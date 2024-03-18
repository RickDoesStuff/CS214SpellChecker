#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// traversing the directories
char** searchFiles(char *dirPath, const char *fileExt, int *numFiles);
char** appendFilePath(char **filePaths, int *size, int *count, const char *filePath);

#endif