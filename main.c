//Sample main.c file that shows how the library works
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#define ll long long
int main(void)
{
    char str[] = "DFS";
    Node root = inputTree();                     // takes input the given format and allocates memory
    printTree2(root);                            // (optional) uses same format as the tree command on bash to print the tree
    traversing_algo(root, root->NoOfNodes, str); // runs the search algorithm based on the comparator
    printstats(root->NoOfNodes);
    DeleteTree(root); // frees the memory of the tree

    // Node root = inputGameTree();
    // printTree3(root);
    // traversing_algo(root, root->NoOfNodes, str);
    // for (int i = 0; i < root->NoOfNodes; i++)
    // {
    //     Print_Game_Node(traversal_order[i]);
    // }
    //DeleteTree(root);
    return 0;
}
