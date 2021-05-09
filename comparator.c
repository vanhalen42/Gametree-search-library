/*===========================================================================================================
This file is a user modifiable file. The user can use this toinput the different parameters that they can   |
define in node.h and build the tree according to their requirements.They can also add functions to print the|
traversal order or even print the tree.                                                                     |
                                                                                                            |
                                                                                                            |
Some in-built print functions have been included for the current state of struct node in the node.h         |
file ,but the user is free to add their code here.                                                          | 
                                                                                                            |
                                                                                                            |
There is an inbuilt function called : Node inputTree(int NoOfNodes);                                        |
->This function returns the pointer to the root of a new tree.                                              |
->It takes total number of your nodes in the input as an argument and calls the input_node(node *a)         |
  function which you can modify in this file. It then tree generates the according to the state numbers of  |
  child and its parent node and gives the user a pointer to it.                                             |
Note. User should only modfiy this file and node.h                                                          |
===========================================================================================================*/

/*=============================================================================================================
The comparator function takes as input the pointers of two nodes and outputs whether the first is 
lesser than the other. User can use this comparator for deciding the order of 2 nodes in the priority queue.
The user is free to change the comparator function (while keeping the argument and return type same) as to their
need .

Check out the input file ./testcases/ts_data_1.txt. It has input of format 
    <number_of_nodes>:n
    <state_number> <data> <parent_state_number>
    ...
    n times
Note: User can change this input according to their wish in intput_node function but the inputTree function 
uses the state number of the node and its parent to generate the tree so those values are mandatory
=============================================================================================================*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"

bool node_comparator(char str[], node *a, node *b) //Selects the required comparator based on the user's choice
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
    else if (strcmp(str, "A* lite") == 0) //this traversal works only for a turn-based game tree (here Tic-Tac-Toe in particular)
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

void printNode(Node TreeNode) //prints the attributes of a node; comment the attributes which do not require to be printed by the user
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