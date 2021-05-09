#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include "node.h"

int checkRow(char ar[3][3], char ch)        //checks if any row of the matrix is filled
{
    for (int i = 0; i < 3; i++)
        if (ar[i][0] == ch && ar[i][1] == ch && ar[i][2] == ch)
            return 1;

    return 0;
}

int checkColumn(char ar[3][3], char ch)     //checks if any column of the matrix is filled
{
    for (int i = 0; i < 3; i++)
        if (ar[0][i] == ch && ar[1][i] == ch && ar[2][i] == ch)
            return 1;

    return 0;
}

int checkDiagonal(char ar[3][3], char ch)       //checks if any diagonal of the matrix is filled
{
    if (ar[0][0] == ch && ar[1][1] == ch && ar[2][2] == ch)
        return 1;
    if (ar[0][2] == ch && ar[1][1] == ch && ar[2][0] == ch)
        return 1;

    return 0;
}

int checkGameOver(Node GameNode)        //return the state of the game at any instance i.e. win, tie, loss or still in play
{
    char temp;

    if (GameNode->game_state == 'X')
        temp = 'O';
    else
        temp = 'X';

    if (checkRow(GameNode->TicTacToe, temp) == 1 || checkColumn(GameNode->TicTacToe, temp) == 1 || checkDiagonal(GameNode->TicTacToe, temp) == 1)
        return 1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (GameNode->TicTacToe[i][j] == '-')
                return 0;

    return 2;
}

int Symmetry(char ar[3][3])         //checks if a 3x3 matrix is Singly Symmetric, Doubly Symmetric, Quadrapuly Symmetric or Non-Symmetric
{
    int sum = 0;

    if (ar[0][0] == ar[0][2] && ar[1][0] == ar[1][2] && ar[2][0] == ar[2][2])
        sum += 1;

    if (ar[0][0] == ar[2][0] && ar[0][1] == ar[2][1] && ar[0][2] == ar[2][2])
        sum += 2;

    if (ar[0][1] == ar[1][0] && ar[0][2] == ar[2][0] && ar[1][2] == ar[2][1])
        sum += 3;

    if (ar[0][0] == ar[2][2] && ar[0][1] == ar[1][2] && ar[1][0] == ar[2][1])
        sum += 4;

    return sum;
}

void AddChild(Node GameNode, int x, int y)      //Adds a child to a given node in a Tic-Tac-Toe game tree
{
    Node Child = (Node)malloc(sizeof(struct node));
    assert(Child != NULL);

    Child->number_of_children = 0;
    Child->depth = GameNode->depth + 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i == x && j == y)
                Child->TicTacToe[i][j] = GameNode->game_state;
            else
                Child->TicTacToe[i][j] = GameNode->TicTacToe[i][j];

    if (GameNode->game_state == 'X')
        Child->game_state = 'O';
    else
        Child->game_state = 'X';

    GameNode->children[GameNode->number_of_children] = Child;
    GameNode->number_of_children++;
}

int calc_heuristic(char a[3][3], char state)        //calculates the heuristic parameter for a given state in Tic-Tac-Toe
{
    int val = 0;
    int X_count = 0, O_count = 0, dash_count = 0;
    if (state == 'O')
    {
        for (int i = 0; i < 3; i++)
        {
            X_count = 0;
            O_count = 0;
            dash_count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (a[i][j] == 'X')
                    X_count++;
                else if (a[i][j] == 'O')
                    O_count++;
                else if (a[i][j] == '-')
                    dash_count++;
            }
            if (dash_count == 3)
                val -= 1;
            else if (X_count == 3)
            {
                val = 50;
                return val;
            }
            else if (O_count > 1 && X_count == 0)
            {
                val = -50;
            }
            else if (O_count == 0)
                val += X_count;
            else if (X_count == 0)
                val -= O_count + 1;
        }
        for (int i = 0; i < 3; i++)
        {
            X_count = 0;
            O_count = 0;
            dash_count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (a[j][i] == 'X')
                    X_count++;
                else if (a[j][i] == 'O')
                    O_count++;
                else if (a[j][i] == '-')
                    dash_count++;
            }
            if (dash_count == 3)
                val -= 1;
            else if (X_count == 3)
            {
                val = 50;
                return val;
            }
            else if (O_count > 1 && X_count == 0)
            {
                val = -50;
            }
            else if (O_count == 0)
                val += X_count;
            else if (X_count == 0)
                val -= O_count + 1;
        }
        X_count = 0;
        O_count = 0;
        dash_count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (a[j][j] == 'X')
                X_count++;
            else if (a[j][j] == 'O')
                O_count++;
            else if (a[j][j] == '-')
                dash_count++;
        }
        if (dash_count == 3)
            val -= 1;
        else if (X_count == 3)
        {
            val = 50;
            return val;
        }
        else if (O_count > 1 && X_count == 0)
        {
            val = -50;
        }
        else if (O_count == 0)
            val += X_count;
        else if (X_count == 0)
            val -= O_count + 1;
        X_count = 0;
        O_count = 0;
        dash_count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (a[j][3 - j - 1] == 'X')
                X_count++;
            else if (a[j][3 - j - 1] == 'O')
                O_count++;
            else if (a[j][3 - j - 1] == '-')
                dash_count++;
        }
        if (dash_count == 3)
            val -= 1;
        else if (X_count == 3)
        {
            val = 50;
            return val;
        }
        else if (O_count > 1 && X_count == 0)
        {
            val = -50;
        }
        else if (O_count == 0)
            val += X_count;
        else if (X_count == 0)
            val -= O_count + 1;
    }
    else if (state == 'X')
    {
        for (int i = 0; i < 3; i++)
        {
            X_count = 0;
            O_count = 0;
            dash_count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (a[i][j] == 'X')
                    X_count++;
                else if (a[i][j] == 'O')
                    O_count++;
                else if (a[i][j] == '-')
                    dash_count++;
            }
            if (dash_count == 3)
                val += 1;
            else if (O_count == 3)
            {
                val = -50;
                return val;
            }
            else if (X_count > 1 && O_count == 0)
            {
                val = 50;
            }
            else if (O_count == 0)
                val += X_count + 1;
            else if (X_count == 0)
                val -= O_count;
        }
        for (int i = 0; i < 3; i++)
        {
            X_count = 0;
            O_count = 0;
            dash_count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (a[j][i] == 'X')
                    X_count++;
                else if (a[j][i] == 'O')
                    O_count++;
                else if (a[j][i] == '-')
                    dash_count++;
            }
            if (dash_count == 3)
                val += 1;
            else if (O_count == 3)
            {
                val = -50;
                return val;
            }
            else if (X_count > 1 && O_count == 0)
            {
                val = 50;
            }
            else if (O_count == 0)
                val += X_count + 1;
            else if (X_count == 0)
                val -= O_count;
        }
        X_count = 0;
        O_count = 0;
        dash_count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (a[j][j] == 'X')
                X_count++;
            else if (a[j][j] == 'O')
                O_count++;
            else if (a[j][j] == '-')
                dash_count++;
        }
        if (dash_count == 3)
            val += 1;
        else if (O_count == 3)
        {
            val = -50;
            return val;
        }
        else if (X_count > 1 && O_count == 0)
        {
            val = 50;
        }
        else if (O_count == 0)
            val += X_count + 1;
        else if (X_count == 0)
            val -= O_count;
        X_count = 0;
        O_count = 0;
        dash_count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (a[j][3 - j - 1] == 'X')
                X_count++;
            else if (a[j][3 - j - 1] == 'O')
                O_count++;
            else if (a[j][3 - j - 1] == '-')
                dash_count++;
        }
        if (dash_count == 3)
            val += 1;
        else if (O_count == 3)
        {
            val = -50;
            return val;
        }
        else if (X_count > 1 && O_count == 0)
        {
            val = 50;
        }
        else if (O_count == 0)
            val += X_count + 1;
        else if (X_count == 0)
            val -= O_count;
    }
    return val;
}

void generateGameTree(Node GameNode)        //generates a game tree for a given turn based game (here Tic-Tac-Toe in particular)
{
    GameNode->heuristic = calc_heuristic(GameNode->TicTacToe, GameNode->game_state);
    GameNode->linktoparent = NULL;
    if (checkGameOver(GameNode) != 0)
        return;

    if (Symmetry(GameNode->TicTacToe) == 1)     //checks for vertical symmetry
        for (int i = 0; i < 3; i++)             //traverses only through left half of the matrix to account for rotational symmetry
            for (int j = 0; j < 2; j++)
                if (GameNode->TicTacToe[i][j] == '-')   //if the cell is empty a move is possible
                    AddChild(GameNode, i, j);

    if (Symmetry(GameNode->TicTacToe) == 2)     //checks for horizontal symmetry
    {                                           //traverses only through upper half of the matrix to account for rotational symmetry
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 2; i++)
                if (GameNode->TicTacToe[i][j] == '-')   // ^^
                    AddChild(GameNode, i, j);
    }

    if (Symmetry(GameNode->TicTacToe) == 3)     //checks for diagonal symmetry
    {                                           //traverses only through upper left diagonal triangle of the matrix to account for rotational symmetry
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (j >= i && GameNode->TicTacToe[i][j] == '-')     // ^^
                    AddChild(GameNode, i, j);
    }

    if (Symmetry(GameNode->TicTacToe) == 4)     //checks for cross diagonal symmetry
    {                                           //traverses only through upper right diagonal triangle of the matrix to account for rotational symmetry
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (i + j <= 2 && GameNode->TicTacToe[i][j] == '-')     // ^^
                    AddChild(GameNode, i, j);
    }
    
    if (Symmetry(GameNode->TicTacToe) == 7)     //checks for bi-diagonal symmetry
    {                                           //traverses only through upper row of the matrix to account for rotational symmetry
        for (int i = 0; i < 3; i++)
            if (GameNode->TicTacToe[0][i] == '-')
                AddChild(GameNode, 0, i);
    }
    
    if (Symmetry(GameNode->TicTacToe) == 10)    //checks for 4-directional symmetry
    {                                           //traverses only through upper right triangle of the matrix to account for rotational symmetry
        if (GameNode->TicTacToe[0][0] == '-')
            AddChild(GameNode, 0, 0);
        if (GameNode->TicTacToe[0][1] == '-')
            AddChild(GameNode, 0, 1);
        if (GameNode->TicTacToe[1][1] == '-')
            AddChild(GameNode, 1, 1);
    }
   
    if (Symmetry(GameNode->TicTacToe) == 0)     //Matrix is Non-Symmetric
        for (int i = 0; i < 3; i++)             //traverses through the entire matrix
            for (int j = 0; j < 3; j++)
                if (GameNode->TicTacToe[i][j] == '-')
                    AddChild(GameNode, i, j);                                       
                                        
    for (int i = 0; i < GameNode->number_of_children; i++)      //generates subtree for each of its children
    {
        generateGameTree(GameNode->children[i]);
    }
}

int calc_num_nodes(Node Game_tree)      //calculates the number of nodes in a game tree
{
    int num = 1;
    for (int i = 0; i < Game_tree->number_of_children; i++)
        num += calc_num_nodes(Game_tree->children[i]);
    return num;
}

void generateTree(Node *NodeArray, int N) //generates a tree out of the array of nodes
{
    for (int i = 1; i < N; i++) //traverses through each node (other than root) and links it to its parent
    {
        Node Temp = NodeArray[NodeArray[i]->parent - 1];
        Temp->children[Temp->number_of_children] = NodeArray[i];
        Temp->children[Temp->number_of_children]->linktoparent = Temp;
        (Temp->number_of_children)++;
        NodeArray[i]->depth = Temp->depth + 1;
        NodeArray[i]->NoOfNodes = INT_MIN;
    }
}

Node inputTree(int NoOfNodes) //takes input from the user and returns a tree
{
    Node *NodeArray = (Node *)malloc(NoOfNodes * sizeof(Node));
    assert(NodeArray != NULL);
    for (int i = 0; i < NoOfNodes; i++) //takes each node as input and feeds it into an array of nodes
    {
        NodeArray[i] = (Node)malloc(sizeof(node));
        assert(NodeArray[i] != NULL);
        input_node(NodeArray[i]);
        NodeArray[i]->number_of_children = 0;
        NodeArray[i]->seen_time = 0;
        NodeArray[i]->numberofchildrenvisited = 0;
    }

    Node Root = NodeArray[0]; //initialises the first node as root of the tree
    Root->depth = 0;
    Root->NoOfNodes = NoOfNodes;
    Root->linktoparent = NULL;
    generateTree(NodeArray, NoOfNodes); //generates the required tree
    free(NodeArray);
    return Root;
}

void printTree(Node TreeNode) //traverses through each node of the tree and prints its attributes
{
    printNode(TreeNode);

    for (int i = 0; i < TreeNode->number_of_children; i++)
        printTree(TreeNode->children[i]);
}

void DeleteTree(Node TreeNode)  //Deletes a given tree and deallocates memory for it
{
    if (TreeNode->number_of_children == 0)
    {
        free(TreeNode);
        return;
    }

    for (int i = 0; i < TreeNode->number_of_children; i++)
    {
        DeleteTree(TreeNode->children[i]);
    }
    free(TreeNode);
}

void printTree2(Node TreeNode)      //Prints an elegant version of a tree
{
    int a[100000] = {0};
    printNodenoice(TreeNode, a);
}

void printNodenoice(Node TreeNode, int what_to_do[])
{

    printf("%d (value : %d)\n", TreeNode->state_number, TreeNode->value);

    for (int i = 0; i < TreeNode->number_of_children; i++)
    {

        for (int i = 0; i < TreeNode->depth; i++)
        {
            if (what_to_do[i])
                printf("      ");
            else
                printf("│     ");
        }
        if (i != TreeNode->number_of_children - 1)
        {
            printf("├─────");
            what_to_do[TreeNode->depth] = 0;
        }
        else if (i == TreeNode->number_of_children - 1)
        {
            printf("└─────");
            what_to_do[TreeNode->depth] = 1;
        }
        printNodenoice(TreeNode->children[i], what_to_do);
    }
}

void printGameNodenoice(Node TreeNode, int what_to_do[])    
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf(" %c", TreeNode->TicTacToe[i][j]);
        printf("\n");
        for (int j = 0; j < TreeNode->depth; j++)
        {
            if (what_to_do[j])
                printf("      ");
            else
                printf("│     ");
        }
    }
    printf("Heuristic: %d\n",TreeNode->heuristic);

    for (int i = 0; i < TreeNode->number_of_children; i++)
    {
        for (int i = 0; i < TreeNode->depth; i++)
        {
            if (what_to_do[i])
                printf("      ");
            else
                printf("│     ");
        }
        if (i != TreeNode->number_of_children - 1)
        {
            printf("├─────");
            what_to_do[TreeNode->depth] = 0;
        }
        else if (i == TreeNode->number_of_children - 1)
        {
            printf("└─────");
            what_to_do[TreeNode->depth] = 1;
        }
        printGameNodenoice(TreeNode->children[i], what_to_do);
    }
}
void printTree3(Node TreeNode)      //prints an elegant version of a Tic-Tac-Toe game tree
{
    int a[100000] = {0};
    printGameNodenoice(TreeNode, a);
}

void free_memory_alloc_stats()      //deallocates memory for the statistical parameters of a tree
{
    free(maxdepth);
    free(maxchildren);
    free(avgdepth);
    return;
}

void Print_Game_Node(Node p)        //Simulates and prints a Tic-Tac-Toe game from a generated game tree
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c ", p->TicTacToe[i][j]);
            if (p->TicTacToe[i][j] == '-')
                count++;
        }
        if (i == 0)

            printf("\t %c's Turn \n", p->game_state);

        else if (i == 1)
            printf("\t Heuristic : %d\n", p->heuristic);
        else
            printf("\n");
    }
    printf("-----------------------\n");
    if (checkGameOver(p))
    {
        printf("=======================\n");
        printf("GAME OVER.\nATERNATE PATHS CAN BE\nSEEN BELOW. \n");
        printf("=======================\n\n\n");
        printf("=======================\n");
    }
    else
    {
        printf("          |          \n");
        printf("          |          \n");
        printf("          V         \n");
        printf("-----------------------\n");
    }
}