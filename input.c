#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

typedef node *Node;

void generateTree(Node *NodeArray, int N)   //generates a tree out of the array of nodes
{
    for (int i = 1; i < N; i++)     //traverses through each node (other than root) and links it to its parent
    {
        Node Temp = NodeArray[NodeArray[i]->parent - 1];
        Temp->children[Temp->number_of_children] = NodeArray[i];
        (Temp->number_of_children)++;
        NodeArray[i]->depth = Temp->depth + 1;
    }
}

Node inputTree()    //takes input from the user and returns a tree
{
    int NoOfNodes;
    scanf("%d", &NoOfNodes);

    Node *NodeArray = (Node *)malloc(NoOfNodes * sizeof(node));

    for (int i = 0; i < NoOfNodes; i++)     //takes each node as input and feeds it into an array of nodes
    {
        NodeArray[i] = (Node)malloc(sizeof(node));
        assert(NodeArray != NULL);
        input_node(NodeArray[i]);
        NodeArray[i]->number_of_children = 0;
        NodeArray[i]->seen_time = 0;
    }

    Node Root = NodeArray[0];   //initialises the first node as root of the tree
    Root->depth = 0;
    generateTree(NodeArray, NoOfNodes);     //generates the required tree
    return Root;
}

void printNode(Node TreeNode)       //prints the attributes of a node
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

void printTree(Node TreeNode)   //traverses through each node of the tree and prints its attributes
{
    printNode(TreeNode);

    for (int i = 0; i < TreeNode->number_of_children; i++)
        printTree(TreeNode->children[i]);
}