#include <stdio.h>
#include <stdlib.h>


#include "spchk.h"
#include "linestream.h"



int main(int argc, char **argv)
{
    // file name
    char *fname = argc > 1 ? argv[1] : "test.txt";
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
    
    // line counter?
    int n = 0;
    
    while ((curLine = next_line(&lines)) && n < 10)
    {
        printf("word:::%d:%s\n", n, curLine);
        //line
        n++;
    }
    lddestroy(&lines);
    return EXIT_SUCCESS;
}