//Sample main.c file that shows how the library works

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#define ll long long
int main(void)
{

    char str[] = "DFS"; //str stors the string which decides which comparator to use

    //Sample code for normal tree
    /*int NoOfNodes;
    scanf("%d",&NoOfNodes);                     //takes input of the number of nodes required for the tree
    
    Node root = inputTree(NoOfNodes);                     // takes input based on the given format and allocates memory
    printTree2(root);                            // (optional) uses same format as the tree command on bash to print the tree
    traversing_algo(root, root->NoOfNodes, str); // runs the search algorithm based on the comparator and stores the order in traversal_order array

    printstats(root->NoOfNodes); // print the traversal_order array
    //(this is an optional step, one can also run a simple for loop from 0 to root->NoOf Nodes)

    DeleteTree(root); // frees the memory of the tree
    free_memory_alloc_stats();  //frees the memory of the statistical parameters of the tree
    free(traversal_order);*/      //frees the memory of traversal array

    // Sample code for in-built Game tree
    /*=========================*/
    
    Node root = inputGameTree();                 // generates a tic-tac-toe game tree from the given initial state
    printTree3(root);                            //(optional) uses same format as the tree command on bash to print the tree
    traversing_algo(root, root->NoOfNodes, str); // runs the search algorithm based on the comparator and stores the order in traversal_order array
    printf("%d\n", root->NoOfNodes);
    // //sample for loop to print traversal order node
     for (int i = 0; i < root->NoOfNodes; i++)
     {
        Print_Game_Node(traversal_order[i]);

        if (checkGameOver(traversal_order[i])) // this condition only prints the most optimal solution, comment it to view other solutions also
            break;
     }
    DeleteTree(root); // frees the memory of the tree
    return 0;
}
