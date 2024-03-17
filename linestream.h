#ifndef LINES_H
#define LINES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// You might want to move these definitions to a central configuration file or remove them
// if they are defined elsewhere.
#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#ifndef __DEBUG
#define __DEBUG 0
#endif

// Structure to hold the state of the file reading iterator
typedef struct {
    int fileDesc;
    int pos;
    int len;
    int size;
    char *buf;
} lines_t;

// Function to initialize the lines_t struct with a given file descriptor
void ldinit(lines_t *lines, int fileDesc);

// Function to free the resources of lines_t struct
void lddestroy(lines_t *lines);

// Function to read the next line from the file
char *next_line(lines_t *lines, int *row, int *col);

#endif // LINES_H
