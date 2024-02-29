#include <stdio.h>
#include <stdlib.h>


#include "spchk.h"
#include "linestream.h"
#include "binaryTree.h"

#ifndef __DEBUG
#define __DEBUG 
#endif

#define DEBUG if(__DEBUG)
#define LOG printf

int main(int argc, char **argv)
{
    // file name
    char *fname = argc > 1 ? argv[1] : "dict_small.txt";


    int fileDesc = open(fname, O_RDONLY);
    if (fileDesc < 0)
    {
        perror(fname);
        exit(EXIT_FAILURE);
    }



    // create lines struct and innit
    lines_t lines;
    ldinit(&lines, fileDesc);

    // create the current line pointer
    char *curLine;
    
    // word counter
    int wordCount = 0;
    

    int arrsize=100;
    char **wordArr = malloc(arrsize * sizeof(char *));

    // load the dictionary
    while ((curLine = next_line(&lines)))
    {
        DEBUG LOG("word:::%d:%s\n", wordCount, curLine);

        wordArr[wordCount]=strdup(curLine); // or make an insert fuction to insert directly into the tree

        wordCount++;

        // if we run out of room in our array
        if (wordCount==arrsize){
            DEBUG LOG("Bigger*2\n");
            arrsize=arrsize*2;
            wordArr=realloc(wordArr,sizeof(char *)*arrsize);
        }
    }
    lddestroy(&lines);

    printf("\n\n\n");
    struct BinaryTreeNode *tree  = buildBalancedBST(wordArr, 0, wordCount - 1);
    preOrder(tree);
    printf("\n\n\n");

    struct BinaryTreeNode *nodeFound=searchBST(tree, "zookk");
    if (nodeFound==NULL){
        printf("Not found.\n");
    } else {
        printf("\n\nfound:%s",nodeFound->key);
    }

    return EXIT_SUCCESS;
}


