#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "node.h"
#define ll long long
void swap(node **a, node **b)
{
    node *c = *a;
    *a = *b;
    *b = c;
}
bool isempty(node *priority_queue[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (priority_queue[i] != NULL)
            return false;
    }
    return true;
}
void traversing_algo(node *root, int n)
{
    node *temp = root;
    node **priority_queue = (node **)malloc(sizeof(node *));
    assert(priority_queue != NULL);
    int queue_size = 0;
    for (int i = 0; i < n; i++)
        priority_queue[i] = NULL;
    assert(queue_size <= n);
    priority_queue[queue_size] = temp;
    queue_size++;
    while (!isempty(priority_queue, n))
    {
        temp = priority_queue[0];
        for (int i = 0; i < temp->number_of_children; i++)
        {
            priority_queue[queue_size] = temp->children[i];
            queue_size++;
            heapify(priority_queue, queue_size - 1, n);
        }
        swap(&priority_queue[0], &priority_queue[queue_size - 1]);
        print_details(priority_queue[queue_size - 1]);
        priority_queue[queue_size - 1] = NULL;
        queue_size--;
        heapify(priority_queue, 0, n);
    }
}
