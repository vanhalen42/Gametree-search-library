#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include "node.h"
#include <math.h>
#include <unistd.h>

typedef struct queue{
    Node* Queue;
    int n;
}queue;

typedef queue* NodeQueue;

long double CalculateUCB(Node GameNode, long int TotalNodesVisited)
{
    long double temp;
    
    if(GameNode->SelectNodeVisit == 0)
        temp = LONG_MAX;
    else
        temp = (((long double) GameNode->WinCount) / ((long double) GameNode->SelectNodeVisit)) + 1.41 * sqrtl( log((long double) TotalNodesVisited) / ((long double) GameNode->SelectNodeVisit));
    
    GameNode->SelectNodeVisit++;
    return temp;
}

void Selection(Node GameNode,NodeQueue Q)
{
    long double max = LONG_MIN;
    Node temp = NULL;

    for(int i = 0 ; i < GameNode->number_of_children; i++)
    {
        if(GameNode->children[i]->UCB > max)
        {
            max = GameNode->children[i]->UCB;
            temp = GameNode->children[i];
        }
    }

    if(temp == NULL)
        return;
    else
    {
        Q->Queue[Q->n] = temp;
        Q->n++;
    }

    Selection(temp,Q);
}

void ExpandGameNode(Node GameNode)
{
    if (checkGameOver(GameNode) != 0)
        return;

    if (Symmetry(GameNode->TicTacToe) == 1)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++)
                if (GameNode->TicTacToe[i][j] == '-')
                    AddChild(GameNode, i, j);

    if (Symmetry(GameNode->TicTacToe) == 2)
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 2; i++)
                if (GameNode->TicTacToe[i][j] == '-')
                    AddChild(GameNode, i, j);

    if (Symmetry(GameNode->TicTacToe) == 3)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (j >= i && GameNode->TicTacToe[i][j] == '-')
                    AddChild(GameNode, i, j);

    if (Symmetry(GameNode->TicTacToe) == 4)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (i + j <= 2 && GameNode->TicTacToe[i][j] == '-')
                    AddChild(GameNode, i, j);

    if (Symmetry(GameNode->TicTacToe) == 7)
        for(int i = 0 ; i < 3 ; i++)
            if(GameNode->TicTacToe[0][i] == '-')
                AddChild(GameNode,0,i);

    if (Symmetry(GameNode->TicTacToe) == 10)
    {
        if (GameNode->TicTacToe[0][0] == '-')
            AddChild(GameNode, 0, 0);
        if (GameNode->TicTacToe[0][1] == '-')
            AddChild(GameNode, 0, 1);
        if (GameNode->TicTacToe[1][1] == '-')
            AddChild(GameNode, 1, 1);
    }

    if (Symmetry(GameNode->TicTacToe) == 0)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (GameNode->TicTacToe[i][j] == '-')
                    AddChild(GameNode, i, j);
}

Node Expansion(NodeQueue Q, Node Root, long int TotalNodesVisited)
{
    Node temp;
    
    if(Q->n == 0)
        temp = Root;
    else
        temp = Q->Queue[Q->n - 1];

    ExpandGameNode(temp);
    for(int i = 0 ; i < temp->number_of_children ; i++)
        temp->children[i]->UCB = CalculateUCB(temp->children[i],TotalNodesVisited);

    return temp;
}

Node GenerateRandomChild(Node GameNode)
{

}

Node RandomChild(Node GameNode)     //wrong...will not work
{
    int i = rand() % GameNode->number_of_children;
    return GameNode->children[i];
}

void SimulatePath(Node GameNode, NodeQueue Q)
{
    if(checkGameOver(GameNode) != 0)
        return;
    
    if((GameNode->heuristic == 50 && GameNode->game_state == 'X') || (GameNode->heuristic == -50 && GameNode->game_state == 'O'))
    {
        GameNode->WinCount = LONG_MIN;
        return;
    }

    Node temp = GenerateRandomChild(GameNode);
    
    while(checkGameOver(temp) == 0)
    {
        Q->Queue[Q->n] = temp;
        Q->n++;
        temp = GenerateRandomChild(temp);
    }

    Q->Queue[Q->n] = temp;
    Q->n++;
}

void Backtrack(NodeQueue Q, int j, long int TotalNodesVisited)
{
    int outcome = checkGameOver(Q->Queue[Q->n - 1]);
    char win_state = '-';
    if(outcome == 1)
        win_state = Q->Queue[Q->n - 1]->game_state;
    
    for(int i = Q->n - 1 ; i >= 0 ; i--)
    {
        if(Q->Queue[i]->game_state == win_state)
            Q->Queue[i]->WinCount++;
        if(i <= j)
            Q->Queue[i]->UCB = CalculateUCB(Q->Queue[i],TotalNodesVisited);
    }
}

void MCTS(Node Root)
{
    if(checkGameOver(Root) != 0)
        return;
    
    srand(time(0));
    time_t t = time(NULL);
    
    NodeQueue Q = (NodeQueue) malloc(sizeof(queue));
    assert(Q != NULL);

    Q->Queue = (Node*) malloc(10*sizeof(Node));
    assert(Q->Queue != NULL);

    Q->n = 0;
    long int TotalNodesVisited = 0;

    while(((double) (time(NULL) - t)  <=  1))
    {        
        Selection(Root,Q);

        int m = Q->n - 1;

        Node temp = Expansion(Q,Root,TotalNodesVisited);
        SimulatePath(temp,Q);
        Backtrack(Q,m,TotalNodesVisited);
    
        for(int i = 0 ; i < Q->n ; i++)
            Q->Queue[i] = NULL;
        Q->n = 0;
    }

    free(Q);
}

void MCTS_traversal(Node GameNode)
{   
    MCTS(GameNode);
    printNode(GameNode);
    //printTree3(GameNode);

    long double max = LONG_MIN;
    Node temp = NULL;

    for(int i = 0 ; i < GameNode->number_of_children; i++)
    {
        if(GameNode->children[i]->UCB > max)
        {
            max = GameNode->children[i]->UCB;
            temp = GameNode->children[i];
        }
    }

    if(temp == NULL)
        return;
        
    DeleteTree2(temp);
    MCTS_traversal(temp);
}

Node inputMCTS()
{
    Node Root = (Node)malloc(sizeof(struct node));
    assert(Root != NULL);

    Root->number_of_children = 0;
    Root->game_state = 'X';

    //uncomment the below snippet to generate complete game tree
    // char ar[3][3] = {{'-','-','-'},
    //                 {'-','-','-'},
    //                 {'-','-','-'}};

    //generates partial game tree with the following initial state
    char ar[3][3] = {{'X', '-', '-'},
                     {'-', 'O', '-'},
                     {'-', '-', '-'}};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Root->TicTacToe[i][j] = ar[i][j];

    return Root;
}