// not tested yet
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "node.h"
#define ll long long
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

void swap(node **a, node **b)
{
    node *c = *a;
    *a = *b;
    *b = c;
}
bool isempty(node *priority_queue[], int n) //checks if the priority queue is empty(1) or not(0)
{
    for (int i = 0; i < n; i++)
    {
        if (priority_queue[i] != NULL)
            return false;
    }
    return true;
}
void heapify(node **priority_queue, int i, int queue_size)
{
    if ((i - 1) / 2 > 0)
    {
        if (node_comparator(priority_queue[i], priority_queue[(i - 1) / 2]))
        {
            swap(&priority_queue[i], &priority_queue[(i - 1) / 2]);
            heapify(priority_queue, (i - 1) / 2, queue_size);
            return;
        }
    }
    if (i * 2 + 1 < queue_size)
    {
        if (i * 2 + 2 >= queue_size)
        {
            if (node_comparator(priority_queue[i * 2 + 1], priority_queue[i]))
            {
                swap(&priority_queue[i], &priority_queue[i * 2 + 1]);
                heapify(priority_queue, i * 2 + 1, queue_size);
                return;
            }
        }
        else
        {
            if (node_comparator(priority_queue[i * 2 + 1], priority_queue[i * 2 + 2]) && node_comparator(priority_queue[i * 2 + 1], priority_queue[i]))
            {
                swap(&priority_queue[i], &priority_queue[i * 2 + 1]);
                heapify(priority_queue, i * 2 + 1, queue_size);
                return;
            }
            else if (node_comparator(priority_queue[i * 2 + 2], priority_queue[i * 2 + 1]) && node_comparator(priority_queue[i * 2 + 2], priority_queue[i]))
            {
                swap(&priority_queue[i], &priority_queue[i * 2 + 2]);
                heapify(priority_queue, i * 2 + 2, queue_size);
                return;
            }
        }
    }
}
void traversing_algo(node *root, int n)
{
    // we make a priority queue of n pointers of type node *
    node **priority_queue = (node **)malloc(n * sizeof(node *));
    assert(priority_queue != NULL);

    int queue_size = 0, seen_time = 0; // declaration and initialization of queue size and time as we go forward
                                       //seen_time updates the seen_time variable of each node when it is inserted into the priority queue
    for (int i = 0; i < n; i++)
        priority_queue[i] = NULL;
    assert(queue_size <= n);

    //root node is added to the priority queue
    priority_queue[queue_size] = root;
    root->seen_time = seen_time;
    seen_time++;
    queue_size++;
    int maxdepthsize = 0;
    // loop for traversal
    long int depths = 0;
    int numberofelems = 1;
    while (!isempty(priority_queue, queue_size)) // while priority queue is not empty
    {
        for (int i = 0; i < priority_queue[0]->number_of_children; i++)
        {
            priority_queue[queue_size] = priority_queue[0]->children[i]; //ith child of current node are added
            priority_queue[0]->children[i]->seen_time = seen_time;       //seen time of the child updated (will be used for comparators)
            seen_time++;
            queue_size++;
            heapify(priority_queue, queue_size - 1, queue_size); //the ith child is added to its correct location in the priority queue using comparator
        }
        swap(&priority_queue[0], &priority_queue[queue_size - 1]); //pop the first element from the priority queue by swapping with last element
        printNode(priority_queue[queue_size - 1]);                 //print the first element which has now been moved to the last
        depths += priority_queue[queue_size - 1]->depth;
        maxdepth[maxdepthsize] = priority_queue[queue_size - 1]->depth;
        bfactor[maxdepthsize] = priority_queue[queue_size - 1]->number_of_children;
        maxdepthsize++;
        avgdepth[numberofelems - 1] = (double)depths / numberofelems;
        numberofelems++;
        priority_queue[queue_size - 1] = NULL;
        queue_size--;
        heapify(priority_queue, 0, queue_size);
    }
    free(priority_queue);
}
