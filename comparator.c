#include <stdio.h>
#include <stdbool.h>
#include "node.h"
//Comparator for DFS (uncomment this and coment others)
/*****************************************************************/
/*
bool node_comparator(node *a, node *b)
{
    // User puts in the node comparator here
    return a->seen_time > b->seen_time; // A sample comparator
}
*/

//Comparator for BFS (uncomment this and coment others)
/*****************************************************************/

bool node_comparator(node *a, node *b)
{
    // User puts in the node comparator here
    return a->seen_time < b->seen_time; // A sample comparator
}

//Comparator for Greedy (uncomment this and coment others)
/*****************************************************************/
/*
bool node_comparator(node *a, node *b)
{
    // User puts in the node comparator here
    return a->value < b->value; // A sample comparator
}
*/
void input_node(node *a)
{
    // inputs the information of one node. Use this in a loop to input all the nodes.
    scanf("%d %d %d", &(a->state_number), &(a->value), &(a->parent));
}