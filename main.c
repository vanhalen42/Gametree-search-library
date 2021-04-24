#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "node.h"
#define ll long long
int main(void)
{
    node *root = inputTree();
    traversing_algo(root, 10);
    // printTree(root);
    return 0;
}