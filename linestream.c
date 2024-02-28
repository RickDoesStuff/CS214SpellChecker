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

#define DEBUG if(__DEBUG)
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

/**
 * Get the next line in the file
 * each line has a different word
*/
char *next_line(lines_t *lines)
{
    // returns NULL at invalid file 
    if (lines->fileDesc < 0)
        return NULL;
    
    // starts reading where cursor left off
    int line_start = lines->pos;
    DEBUG LOG("[%d]: pos %d/len %d\n", lines->fileDesc, lines->pos, lines->len);
    
    while (1)
    {

        if (lines->pos == lines->len)
        {

            // expanding the buffer
            if (line_start == 0 && lines->len == lines->size)
            {
                lines->size *= 2;
                lines->buf = realloc(lines->buf, lines->size);

                DEBUG LOG("[%d]: expand buffer to %d\n", lines->fileDesc, lines->size);
            }
            
            // buffer doesnt eed to be expanded
            else if (line_start < lines->pos)
            {
                int segment_length = lines->pos - line_start;
                memmove(lines->buf, lines->buf + line_start, segment_length);
                lines->pos = segment_length;
            }
            
            // start of file
            else
            {
                DEBUG LOG("\nStart of new file\n");
                lines->pos = 0;
            }
            int bytes = read(lines->fileDesc, lines->buf + lines->pos, lines->size - lines->pos);

            // breaks if reads error?
            if (bytes < 1)
            {
                DEBUG LOG("Breaking from loop\n");
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
        // Punctuation is not handled, thank you Mendy
        // TODO: hyphens and punctuation
        if (lines->buf[lines->pos] == ' ') {
            // put string terminator onto end of buffer
            DEBUG LOG ("end of word\n");

            lines->buf[lines->pos] = '\0';

            lines->pos++;
            return lines->buf + line_start;
        }
        // detects end of a line
        else if (lines->buf[lines->pos] == '\n')
        {
            // put string terminator onto end of buffer
            DEBUG LOG ("end of line\n");
            lines->buf[lines->pos] = '\0';
            
            // increase the lines counter
            lines->pos++;
            return lines->buf + line_start;
        }
        // not end of word or line
        else
        {
            lines->pos++;
        }
    }

    // Reached end of the file
    // printf("Reached EOF");
    close(lines->fileDesc);
    lines->fileDesc = -1;

    DEBUG LOG("Lstart:%i,Lpos:%i,Lsize:%i\n", line_start, lines->pos,lines->size);

    // some weird size issue
    if (line_start < lines->pos)
    {
        DEBUG LOG("start<pos\n");
        if (lines->pos == lines->size)
        {
            lines->buf = realloc(lines->buf, lines->size + 1);
        }
        lines->buf[lines->pos] = '\0';
        return lines->buf + line_start;
    }
    lines->buf[lines->pos] = '\0';
    return lines->buf;
    //return NULL;
}
