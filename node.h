/*
    The idea behind Tree Search Library is that, once given the 'comparator' function between nodes by 
    the user, the library can use this to perform any kind of search by the change of just one function.
    
    The comparator function takes as input the pointers of two nodes and outputs whether the first is 
    lesser than the other. You can use this comparator for deciding the order of 2 nodes in the priority 
    queue.

    This file will be what the user will edit, while trying to use your library. Once you complete writing
    the library, you have to (as an user of the library), write the comparators for DFS, BFS, greedy 
    search (A-star lite).

    Check out the input file ts_data_1.txt. It has input of format 
    <number_of_nodes>:n
    <state_number> <value> <parent_state_number>
    ...
    n times

    For now, write the main function and input the nodes, fill the values of number_of_children, children
    (in the struct) and try to write the priority queue using the comparator.
*/

#include <stdio.h>
#include <stdbool.h>

typedef struct node
{
    int state_number;
    int value;
    int parent;

    // You (as a developer) can add any extra information here [Will not be touched by user]
    int depth, seen_time, number_of_children;
    struct node *children[10000];
}node;

bool node_comparator(node *a, node *b)
{
    // User puts in the node comparator here
    return a->value < b->value; // A sample comparator
}

void input_node(node *a)
{
    // inputs the information of one node. Use this in a loop to input all the nodes.
    scanf("%d %d %d", &(a->state_number), &(a->value), &(a->parent));
}