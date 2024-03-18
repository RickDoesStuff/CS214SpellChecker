#include "filestream.h"


char* searchFiles(char *dirPath, const char *fileExt, int *numFiles) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Open directory
    if ((dir = opendir(dirPath)) != NULL) {
        // Traverse directory entries
        while ((entry = readdir(dir)) != NULL) {
            // Skip '.' and '..' entries
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            // Construct full path
            char fullPath[PATH_MAX];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, entry->d_name);

            // Get file info
            if (stat(fullPath, &fileStat) == -1) {
                perror("stat");
                continue;
            }

            // Check if it's a directory
            if (S_ISDIR(fileStat.st_mode)) {
                // Recursively search in subdirectories
                char* result = searchFile(fullPath, fileExt);
                if (result != NULL)
                    return result;
            } else {
                // Check if file ends with the specified extension
                char *extension = strrchr(entry->d_name, '.');
                if (extension != NULL && strcmp(extension, fileExt) == 0) {
                    // Found the file
                    char* fullPathCopy = malloc(strlen(fullPath) + 1);
                    strcpy(fullPathCopy, fullPath);
                    closedir(dir);
                    return fullPathCopy;
                }
            }
        }
        // Close directory
        closedir(dir);
    } else {
        // Failed to open directory
        perror("opendir");
    }
    
    return NULL; // File not found
}