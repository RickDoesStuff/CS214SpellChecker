#include "filestream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

char **searchFiles(char *dirPath, const char *fileExt, int *numFiles) {
    printf("search files called\n");
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char **filePaths = NULL;
    int count = 0;

    // Open directory
    if ((dir = opendir(dirPath)) != NULL) {
        
        // Traverse directory entries
        while ((entry = readdir(dir)) != NULL) 
        {
            // Skip '.' and '..' entries
            printf("filename:%s\n",entry->d_name);
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            // Construct full path
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

            // Safely append the file name to fullPath
            strncat(fullPath, entry->d_name, PATH_MAX - strlen(fullPath) - 1);

            // Get file info
            if (stat(fullPath, &fileStat) == -1) {
                printf("Full Path: %s\n", fullPath);
                perror("stat");
                continue;
            }

            // Check if it's a directory
            if (S_ISDIR(fileStat.st_mode)) {

                // Recursively search in subdirectories
                char **subDirFiles = searchFiles(fullPath, fileExt, &count);

                // this merges the file list with the current file list
                if (subDirFiles != NULL) {
                    
                    for (int i = 0; i < count; i++) {

                        filePaths = realloc(filePaths, (count + i + 1) * sizeof(char *));
                        filePaths[i] = strdup(fullPath);
                        i++;
                    }

                    // frees after merging the list
                    free(subDirFiles);
                }

            } else {

                // Check if file ends with the specified extension
                char *extension = strrchr(entry->d_name, '.');

                if (extension != NULL && strcmp(extension, fileExt) == 0) {
                    // Found the file
                    filePaths = realloc(filePaths, (count + 1) * sizeof(char *));
                    filePaths[count] = strdup(fullPath);
                    count++;
                }
            }
        }

        // Close directory
        closedir(dir);

    } else {

        // Failed to open directory
        perror("opendir");

    }

    *numFiles = count;
    
    return filePaths;
}