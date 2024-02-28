#include <stdio.h>
#include <stdlib.h>


#include "spchk.h"
#include "linestream.h"
#include "binaryTree.h"


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
    
    // word counter?
    int wordCount = 0;
    

    int arrsize=100;
    char **wordArr=malloc(arrsize * sizeof(char *));

    while ((curLine = next_line(&lines)))
    {
        printf("word:::%d:%s\n", wordCount, curLine);
        
        wordArr[wordCount]=strdup(curLine);

        free(curLine);
        wordCount++;

        // if we run out of room in our array
        if (wordCount==arrsize){
            arrsize=arrsize*2;
            wordArr=realloc(wordArr,sizeof(char *)*arrsize);
        }
    }
    for(int i = 0 ;i<wordCount;i++){
        printf(" %s ",wordArr[i]);
    }
    printf("\n\n\n");
    struct BinaryTreeNode *tree  = buildBalancedBST(wordArr,0, wordCount - 1);
    preOrder(tree);
    lddestroy(&lines);
    return EXIT_SUCCESS;
}


