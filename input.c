#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

typedef node* Node;

void generateTree(Node* NodeArray, int N)
{
    for(int i = 1 ; i < N ; i++)
    {
        Node Temp = NodeArray[NodeArray[i]->parent - 1];
        Temp->children[Temp->number_of_children] = NodeArray[i];
        (Temp->number_of_children)++;
        NodeArray[i]->depth = Temp->depth + 1;
    }
}

Node inputTree()
{
    int NoOfNodes;
    scanf("%d",&NoOfNodes);

    Node* NodeArray = (Node*) malloc(NoOfNodes*sizeof(node));

    for(int i = 0 ; i < NoOfNodes ; i++)
    {
        NodeArray[i] = (Node) malloc(sizeof(node));
        assert(NodeArray != NULL);
        input_node(NodeArray[i]);
        NodeArray[i]->number_of_children = 0;
        NodeArray[i]->seen_time = 0;
    }

    Node Root = NodeArray[0];
    Root->depth = 0;
    generateTree(NodeArray,NoOfNodes);
    return Root;
}

void printNode(Node TreeNode)
{
    printf("State Number: %d\n",TreeNode->state_number);
    printf("Value: %d\n",TreeNode->value);
    if(TreeNode->parent = -1)
        printf("Parent: -\n");
    else
        printf("Parent: %d\n",TreeNode->parent);
    printf("Depth: %d\n",TreeNode->depth);
    printf("Seen Time: %d\n",TreeNode->seen_time);
    printf("\nNumber of Children: %d\n",TreeNode->number_of_children);
    
    if(TreeNode->number_of_children == 0)
    {
        printf("Children: -\n\n");
        return;
    }

    printf("Children: ");
    for(int i = 0 ; i < TreeNode->number_of_children ; i++)
        printf("%d ",TreeNode->children[i]->value);
    printf("\n\n");
}

void printTree(Node TreeNode)
{
    printNode(TreeNode);

    for(int i = 0 ; i < TreeNode->number_of_children ; i++)
        printTree(TreeNode->children[i]);
}

int main()
{
    Node Root = inputTree();
    printTree(Root);    
}