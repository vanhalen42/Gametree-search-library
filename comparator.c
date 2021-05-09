#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"

bool node_comparator(char str[], node *a, node *b)      //Selects the required comparator based on the user's choice
{
    if (strcmp(str, "DFS") == 0)
    {
        return a->seen_time > b->seen_time;
    }
    else if (strcmp(str, "BFS") == 0)
    {
        return a->seen_time < b->seen_time;
    }
    else if (strcmp(str, "Greedy") == 0)
    {
        return a->value < b->value;
    }
    else if (strcmp(str, "A* lite") == 0)       //this traversal works only for a turn-based game tree (here Tic-Tac-Toe in particular)
    {
        if (a->depth == b->depth)
        {
            if (a->game_state == b->game_state && a->game_state == 'X')
                return a->heuristic < b->heuristic;
            else if (a->game_state == b->game_state && a->game_state == 'O')
                return a->heuristic > b->heuristic;
            else
                return 0;
        }
        else
            return a->seen_time > b->seen_time;
    }
    else
        return a->seen_time > b->seen_time;
}

void input_node(node *a)
{
    // inputs the information of one node. Use this in a loop to input all the nodes.
    scanf("%d %d %d", &(a->state_number), &(a->value), &(a->parent));
}

Node inputGameTree()
{
    Node Root = (Node)malloc(sizeof(struct node));
    assert(Root != NULL);

    Root->number_of_children = 0;
    Root->game_state = 'O';
    Root->depth = 0;

    //uncomment the below snippet to generate complete game tree from scratch
    // char ar[3][3] = {{'-', '-', '-'},
    //                  {'-', '-', '-'},
    //                  {'-', '-', '-'}};

    //generates complete game tree with the following initial state (can be changed)
    char ar[3][3] = {{'X', '-', '-'},
                     {'-', 'O', '-'},
                     {'-', '-', 'X'}};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Root->TicTacToe[i][j] = ar[i][j];

    generateGameTree(Root);
    Root->NoOfNodes = calc_num_nodes(Root);
    return Root;
}

void printNode(Node TreeNode)   //prints the attributes of a node; comment the attributes which do not require to be printed by the user
{
    printf("State Number: %d\n", TreeNode->state_number);
    printf("Value: %d\n", TreeNode->value);
    
    if (TreeNode->parent == -1)
        printf("Parent: -\n");
    else
        printf("Parent: %d\n", TreeNode->parent);
    
    printf("Depth: %d\n", TreeNode->depth);
    printf("Seen Time: %d\n", TreeNode->seen_time);
    printf("\nNumber of Children: %d\n", TreeNode->number_of_children);

    if (TreeNode->number_of_children == 0)
    {
        printf("Children: -\n\n");
        return;
    }

    printf("Children: ");
    for (int i = 0; i < TreeNode->number_of_children; i++)
        printf("%d ", TreeNode->children[i]->value);
    printf("\n\n");
}