#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
        // or make an insert fuction to insert directly into the tree
        wordArr[wordCount]=strdup(curLine);
        wordCount++;
        
        // if we run out of room in our array
        if (wordCount==arrsize){
            DEBUG LOG("Bigger*2\n");
            arrsize=arrsize*2;
            wordArr=realloc(wordArr,sizeof(char *)*arrsize);
        }

        // make the words capital as well
        char tempWord[75];
        int i;
        for (i = 0; curLine[i]; i++) 
        {
            char chr = curLine[i]; 
            tempWord[i] = toupper(chr); 
        }
        tempWord[strlen(curLine)]='\0';
        wordArr[wordCount]=strdup(tempWord);
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
    // create the binary tree
    struct BinaryTreeNode *tree  = buildBalancedBST(wordArr, 0, wordCount - 1);
    preOrder(tree);
    printf("\n\n\n");


    // check words
    char *words[]={"zoom","ZOOM","Zoom","MacDonald","MACDONALD","macDonald"};
    
    for (int i=0; words[i]; i++)
    {
        searchDict(tree,words[i]);
    }



    return EXIT_SUCCESS;
}