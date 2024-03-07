#include <stdlib.h>
#include <stdio.h>

#include "binaryTree.h"
#include "dictSearch.h"

//https://www.geeksforgeeks.org/c-program-for-binary-search-tree/

#ifndef __DEBUG
#define __DEBUG 
#endif

#define DEBUG if(__DEBUG)
#define LOG printf


int search(struct BinaryTreeNode *tree, char** word) 
{
    struct BinaryTreeNode *nodeFound = searchBST(tree, *word);
    if (nodeFound==NULL){
        printf("Not found.\n");
    } else {
        printf("\n\nfound:%s",nodeFound->key);
    }
}