#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "spchk.h"
#include "linestream.h"
#include "binaryTree.h"


int main(int argc, char **argv)
{
    // file names
    char *fname = argc > 1 ? argv[1] : "dict_small.txt";
    char *fparagraph = argc > 2 ? argv[2] : "paragraph.txt";

    // open dictionary file
    int fileDesc = open(fname, O_RDONLY);
    if (fileDesc < 0)
    {
        perror(fname);
        exit(EXIT_FAILURE);
    }

    // open paragraph file
    int fileDesc2 = open(fparagraph, O_RDONLY);
    if (fileDesc < 0)
    {
        perror(fparagraph);
        exit(EXIT_FAILURE);
    }

    // create lines struct and innit
    lines_t lines;
    ldinit(&lines, fileDesc);

    // create the current line pointer
    char *curLine;
    
    // word counter
    int wordCount = 0;

    // location of word in paragraph
    int row = 1;
    int col = 0;
    

    int arrsize=100;
    char **wordArr = malloc(arrsize * sizeof(char *));
    char **wordArrCAPS = malloc(arrsize * sizeof(char *));

    // load the dictionary
    while ((curLine = next_line(&lines, NULL, NULL)))
    {
        DEBUG LOG("word:::%d:%s\n", wordCount, curLine);
        // or make an insert fuction to insert directly into the tree
        
        wordArr[wordCount]=strdup(curLine);

        // make the words capital as well
        char tempWord[75];
        int i;
        for (i = 0; curLine[i]; i++) 
        {
            char chr = curLine[i]; 
            tempWord[i] = toupper(chr); 
        }
        tempWord[strlen(curLine)]='\0';
        wordArrCAPS[wordCount]=strdup(tempWord);

        wordCount++;

        // if we run out of room in our array
        if (wordCount==arrsize){
            DEBUG LOG("Bigger*2\n");
            arrsize=arrsize*2;
            wordArrCAPS=realloc(wordArrCAPS,sizeof(char *)*arrsize);
            wordArr=realloc(wordArr,sizeof(char *)*arrsize);
        }
    }

    DEBUG LOG("\n\nword45:%s\n\n",wordArr[45]);

    lddestroy(&lines);

    DEBUG LOG("\n\nword45:%s\n\n",wordArr[45]);
    
    
    printf("\n\n\n");
    // create the binary tree
    struct BinaryTreeNode *tree  = buildBalancedBST(wordArr, 0, wordCount - 1);
    DEBUG preOrder(tree);
    DEBUG printf("\n\n\n");
    // create the CAPS binary tree
    struct BinaryTreeNode *treeCaps  = buildBalancedBST(wordArrCAPS, 0, wordCount - 1);
    DEBUG preOrder(treeCaps);
    DEBUG printf("\n\n\n");

    DEBUG LOG("\n\nword45:%s\n\n",wordArr[45]);

    // check words
    // char *words[]={"zoom","ZOOM","Zoom","MacDonald","MACDONALD","macDonald"};

    // read the paragraph file
    lines_t lines2;
    ldinit(&lines2, fileDesc2);

    while ((curLine = next_line(&lines2, &row, &col)))
    {
        DEBUG LOG("word:::%s\n", curLine);
        if (searchDict(tree,treeCaps,curLine) == 0)
        {
            printf("Word missspelled at:%d:%d::%s\n",row,col,curLine);
        }

    }
    lddestroy(&lines2);

    
    //printf("hello found:%i\n",searchDict(tree,treeCaps,"hello"));
    //printf("HELLO found:%i\n",searchDict(tree,treeCaps,"HELLO"));
    
    // for (int i=0; words[i]; i++)
    // {
    //     searchDict(tree,treeCaps,words[i]);
    // }


    DEBUG LOG("\n\n\n");
    DEBUG preOrder(tree);
    DEBUG LOG("\n\n\n");
    DEBUG preOrder(treeCaps);

    return EXIT_SUCCESS;
}