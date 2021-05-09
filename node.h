#ifndef NODE_H
#define NODE_H
/*=============================================================================================================
This is a user modifable file. It contains the struct node whcih has user modifiable sections where the user is 
to add paramters or any extra information.
=============================================================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
typedef struct node
{
    int state_number;
    int value;
    int parent;

    // You (as a developer) can add any extra information here [Will not be touched by user]
    int depth, seen_time, number_of_children, NoOfNodes;
    char game_state;      //
    char TicTacToe[3][3]; //
    struct node *children[10000];
    struct node *linktoparent;   //links the node to its parent
    int heuristic;               //used for the game tree. stores a parameter that gives the closeness to end of game
    int numberofchildrenvisited; //number of children of the node visited during the search
} node;
typedef node *Node;

int *maxdepth;
double *avgdepth;
//int bfactor[10000];
int *maxchildren;
Node *traversal_order;

bool node_comparator(char str[], node *a, node *b);
void input_node(node *a);

void generateTree(Node *NodeArray, int N); //generates a tree out of the array of nodes
Node inputTree(int NoOfNodes);             //takes input from the user and returns a tree
void printNode(Node TreeNode);             //prints the attributes of a node
void printTree(Node TreeNode);             //traverses through each node of the tree and prints its attributes
void printTree2(Node TreeNode);            //shows the structure of the tree while printing minimal information (the state number and value)
void DeleteTree(Node TreeNode);            //Frees memory allocated to the tree

Node inputGameTree();
void generateGameTree(Node GameNode);
void printTree3(Node GameNode);
int calc_num_nodes(Node Game_tree);
void Print_Game_Node(Node p);
int checkGameOver(Node GameNode);
int Symmetry(char ar[3][3]);

void traversing_algo(node *root, int n, char str[]);
void printNodenoice(Node TreeNode, int what_to_do[]);
void printstats(int N);
void free_memory_alloc_stats();
#endif