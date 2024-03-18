// Reading through a file by line, non-allocating iterator-style.
//
// This code puts all the file-reading logic into next_line,
// which returns a freshly allocated string, or NULL at EOF.
//
// The lines_t structure holds the state of the iterator,
// which is a buffer and the current position in the buffer.
// next_line automatically refreshes the buffer as needed while
// constructing the next line.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "linestream.h"

#ifndef BUFSIZE
#define BUFSIZE 128
#endif

#ifndef __DEBUG
#define __DEBUG
#endif

#define DEBUG if (__DEBUG)
#define LOG printf

void ldinit(lines_t *lines, int fileDesc)
{
    lines->fileDesc = fileDesc;
    lines->pos = 0;
    lines->len = 0;
    lines->size = BUFSIZE;
    lines->buf = malloc(BUFSIZE);
}

/**
 * Free the line struct
 */
void lddestroy(lines_t *lines)
{
    if (lines->fileDesc >= 0)
    {
        close(lines->fileDesc);
        lines->fileDesc = -1;
    }
    free(lines->buf);
}

// intialize the line counters
int actualRow = 1;
int actualCol = 1;

/**
 * Get the next line in the file
 * each line has a different word
 */

char *next_word(lines_t *lines, int *row, int *col)
{
    if (col != NULL && row != NULL)
    {
        *col = actualCol;
        *row = actualRow;
    }
    // returns NULL at invalid file
    if (lines->fileDesc < 0)
        return NULL;

    // starts reading where cursor left off
    int line_start = lines->pos;
    DEBUG LOG("[%d]: pos %d/len %d\n", lines->fileDesc, lines->pos, lines->len);

    while (1)
    {
        // if the pos is greater or equal to the max size, expand the buffer
        if (lines->pos >= lines->len)
        {
            // expanding the buffer
            if (line_start == 0 && lines->len == lines->size)
            {
                lines->size *= 2;
                lines->buf = realloc(lines->buf, lines->size);
                DEBUG LOG("[%d]: expand buffer to %d\n", lines->fileDesc, lines->size);
            }

            // buffer doesnt need to be expanded
            else if (line_start < lines->pos)
            {
                // printf("no buffer expansion\n");
                int segment_length = lines->pos - line_start;
                memmove(lines->buf, lines->buf + line_start, segment_length);
                lines->pos = segment_length;
            }
            // start of file
            else
            {
                printf("row gets reset here.\n");
                DEBUG LOG("\nStart of new file\n");
                lines->pos = 0;
                if (row != NULL && col != NULL)
                {
                    actualRow = 1;
                    actualCol = 1;
                    *row = actualRow;
                    *col = actualCol;
                }
            }
            int bytes = read(lines->fileDesc, lines->buf + lines->pos, lines->size - lines->pos);

            // breaks if reads error?
            if (bytes < 1)
            {
                // printf("Breaking from loop\n");
                break;
            }
            lines->len = lines->pos + bytes;
            line_start = 0;
            DEBUG LOG("[%d]: Read %d bytes\n", lines->fileDesc, bytes);
        }

        DEBUG LOG("[%d]: %d/%d/%d/%d '%c'\n",
                  lines->fileDesc, line_start, lines->pos, lines->len, lines->size, lines->buf[lines->pos]);

        // detects end of a word!
        // doesnt work with hyphens right now
        // TODO: hyphens and punctuation
        if (lines->buf[lines->pos] == ' ' || lines->buf[lines->pos] == '\n')
        {
            // put string terminator onto end of buffer
            DEBUG LOG("end of word\n");

            // if col is not null
            if (col != NULL)
            {
                // increase the row counter and reset col counter when a newline appears
                if (lines->buf[lines->pos] == '\n')
                {
                    actualRow++;
                    actualCol = 1;
                    DEBUG LOG("lineCount:%i,wordCount:%i\n", *row, *col);
                    // increase the line counter after everything else
                }
                // increase the actual col counter if a space appears
                else if (lines->buf[lines->pos] == ' ')
                {
                    // increase the actual col counter
                    if (col != NULL)
                    {
                        *col = actualCol;
                        actualCol++;
                    }
                }
            }

            // this stuff kinda works
            // Skip leading punctuation: Adjust line_start to the first non-punctuation character
            int numOfPunct = 0;
            while (line_start < lines->pos && ispunct(lines->buf[line_start]))
            {
                line_start++;
                numOfPunct++;
            }
            if (col != NULL)
            {
                *col += numOfPunct;
                // printf ("After Punct:Col:%i,Row:%i\n",*col,actualRow);
            }

            // Find the end of the word, skipping trailing punctuation
            int word_end = lines->pos - 1;
            while (word_end > line_start && ispunct(lines->buf[word_end]))
            {
                word_end--;
            }

            // Place the string terminator right after the last non-punctuation character of the word
            lines->buf[word_end + 1] = '\0';

            // lines->buf[lines->pos] = '\0';

            lines->pos++;

            // checks if returning whitespace
            if (!isspace(lines->buf[lines->pos]))
            {
                // printf("\n\n\n\n******\nchar:%c\nlines->pos:%i\nline_start:%i\nword_end:%i\nword:%s\n",lines->buf[lines->pos-1],lines->pos,line_start,word_end,lines->buf + line_start);
                // return NULL;
                return lines->buf + line_start;
            }
        }
        // no space or newline
        else
        {
            lines->pos++;
            // increase the *col
            if (col != NULL)
            {
                actualCol++;
            }
        }
    }

    // Reached end of the file
    // printf("Reached EOF");
    close(lines->fileDesc);
    lines->fileDesc = -1;

    // need this when reading the last word of the paragraph
    // for some reason it does not increase the last col count
    // when breaking from the loop
    if (row != NULL && col != NULL)
    {
        *col = actualCol;
        actualCol++;
    }

    DEBUG LOG("Lstart:%i,Lpos:%i,Lsize:%i\n", line_start, lines->pos, lines->size);

    // some weird size issue
    if (line_start < lines->pos)
    {
        DEBUG LOG("start<pos\n");
        if (lines->pos == lines->size)
        {
            lines->buf = realloc(lines->buf, lines->size + 1);
        }
        lines->buf[lines->pos] = '\0';
        // printf("returning here 1\n");
        return lines->buf + line_start;
    }

    // this is where the issue is happening
    line_start = 0;
    // Skip leading punctuation: Adjust line_start to the first non-punctuation character
    while (ispunct(lines->buf[line_start]))
    {
        line_start++;
    }
    if (col != NULL)
    {
        *col += line_start;
    }

    // // If we reach the end of the buffer while skipping leading punctuation, return NULL to indicate no more words
    // if (line_start == lines->pos) {
    //     return NULL; // Or handle appropriately based on your requirements
    // }

    // Find the end of the word, skipping trailing punctuation
    // printf("***before lines->pos:%i\n",lines->pos);
    int word_end = lines->pos - 1;
    while (ispunct(lines->buf[word_end]))
    {
        word_end--;
        // printf("word_end:%i\n",word_end);
    }

    // Place the string terminator right after the last non-punctuation character of the word
    lines->buf[word_end + 1] = '\0';

    //*col+=line_start;

    if (strlen(lines->buf) == 0)
    {
        DEBUG printf("ret null\n");
        return "";
    }
    // printf("returning here 2\n");
    // lines->buf[lines->pos] = '\0';
    return lines->buf + line_start;
    // return NULL;
}