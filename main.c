//Sample main.c file that shows how the library works

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#define ll long long
int main(void)
{

    char str[] = "Greedy"; //str stors the string which decides which comparator to use

    //Sample code for normal tree
    Node root = inputTree();                     // takes input the given format and allocates memory
    printTree2(root);                            // (optional) uses same format as the tree command on bash to print the tree
    traversing_algo(root, root->NoOfNodes, str); // runs the search algorithm based on the comparator and stores the order in traversal_order array

    printstats(root->NoOfNodes); // print the traversal_order array
    //(this is an optional step, one can also run a simple for loop from 0 to root->NoOf Nodes)

    DeleteTree(root); // frees the memory of the tree

    // Sample code for in-built Game tree
    /*=========================*/
    /*
    Node root = inputGameTree();                 // generates a tic-tac-toe game tree from the given initial state
    printTree3(root);                            //(optional) uses same format as the tree command on bash to print the tree
    traversing_algo(root, root->NoOfNodes, str); // runs the search algorithm based on the comparator and stores the order in traversal_order array

    //sample for loop to print traversal order node
    for (int i = 0; i < root->NoOfNodes; i++)
    {
        Print_Game_Node(traversal_order[i]);

        if (checkGameOver(traversal_order[i])) // this condition only prints the most optimall solution, commentit to view other solutions also
            break;
    }
    DeleteTree(root); // frees the memory of the tree
    */
    return 0;
}
