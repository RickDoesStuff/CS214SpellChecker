#include "filestream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif


/**
 * Appends the current file directory to the list of directories
 * returns the list of directories
*/
char** appendFilePath(char **filePaths, int *size, int *count, const char *filePath) {
    if (*count >= *size) {
        *size *= 2; // Double the size
        filePaths = realloc(filePaths, sizeof(char *) * (*size));
        if (!filePaths) {
            printf("Failed to realloc filePaths!!");
            exit(EXIT_FAILURE);
        }
    }
    filePaths[*count] = strdup(filePath); // Duplicate the file path
    if (!filePaths[*count]) {
        printf("Failed to duplicate filePath!!");
        exit(EXIT_FAILURE);
    }
    (*count)++;
    return filePaths;
}

/**
 * Searches for files in the given directory including all sub directories
 * returns a list of all the paths containing the given extension
*/
char** searchFiles(char *dirPath, const char *fileExt, int *numFiles) {
    //printf("\n\nsearch files called\n");
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    int count = 0;
    int size = 1;

    char **filePaths = malloc(sizeof(char *) * size);
    if (!filePaths) {
        printf("Failed to malloc memory for filePaths!!");
        exit(EXIT_FAILURE);
    }


    // Open directory
    if ((dir = opendir(dirPath)) != NULL) {
        
        // Traverse directory entries
        while ((entry = readdir(dir)) != NULL) 
        {
            //printf("filename:%s\n",entry->d_name);

            // Skip '.' and '..' entries
            // and other entries that start with '.'
            if (entry->d_name[0] == '.') {
                continue;
            }

            // make full path
            char fullPath[PATH_MAX];
            fullPath[0] = '\0'; // Ensure the buffer starts empty and null-terminated

            // Safely copy directory path to fullPath
            strncpy(fullPath, dirPath, PATH_MAX - 1);
            fullPath[PATH_MAX - 1] = '\0'; // Null-terminate to be safe

            // Check if the last character of dirPath is not already a '/', add it if necessary
            int len = strlen(fullPath);
            if(len < PATH_MAX - 1 && fullPath[len - 1] != '/') {
                fullPath[len] = '/';
                fullPath[len + 1] = '\0'; // Ensure null-termination after adding '/'
            }

            // concat the file name to fullPath
            strncat(fullPath, entry->d_name, PATH_MAX - strlen(fullPath) - 1);

            // file info
            if (stat(fullPath, &fileStat) == -1) {
                printf("Full Path: %s\n", fullPath);
                printf("stat");
                continue;
            }
            
            //printf("\nFull Path: %s\n", fullPath);

            // Check if it's a directory
            if (S_ISDIR(fileStat.st_mode)) {

                // Recursively search in subdirectories
                int subDirCount = 0;
                char **subDirFiles = searchFiles(fullPath, fileExt, &subDirCount);
                for (int i = 0; i < subDirCount; i++) {
                    
                    // appens file to filePaths
                    filePaths = appendFilePath(filePaths, &size, &count, subDirFiles[i]);
                    free(subDirFiles[i]); // Free the string after appending
                }
                free(subDirFiles); // Free the subdirectory array
            } else {
                
                // Check if file ends with the specified extension
                char *extension = strrchr(entry->d_name, '.');
                if (extension == NULL) {return NULL;}
                
                // see if the current extension matches the fileExt we give it
                if (strcmp(extension, fileExt) == 0) {

                    // Append file path to the array
                    filePaths = appendFilePath(filePaths, &size, &count, fullPath);
                }
            }
        }

        // Close directory
        closedir(dir);

    } else {
        // Failed to open directory
        printf("opendir error!!");
        free(filePaths);
        return NULL;
    }

    *numFiles = count;
    return filePaths;
}