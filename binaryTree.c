#include "binaryTree.h"
#include <ctype.h>


#ifndef __DEBUG
#define __DEBUG
#endif

#define DEBUG if(__DEBUG)
#define LOG printf

// https://www.geeksforgeeks.org/c-program-for-binary-search-tree/
// https://www.codesdope.com/blog/article/binary-search-tree-in-c/
// https://www.freecodecamp.org/news/binary-search-trees-bst-explained-with-examples/

/**
 * Function to create a new node with a given value
*/
struct BinaryTreeNode* newNodeCreate(char* value) {
    struct BinaryTreeNode* temp = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));

    // make sure temp is not null
    if (temp == NULL) {
        perror("Unable to allocate memory for new node");
        return NULL;
    }

    // Duplicate the string
    temp->key = strdup(value); 
    // make sure value got stored
    if (temp->key == NULL) {
        free(temp);
        perror("Unable to allocate memory for node key");
        return NULL;
    }

    // set the leaves of this node to null
    temp->left = temp->right = NULL;
    return temp;
}


//strcmp(char1,char2);
struct BinaryTreeNode* insertNode(struct BinaryTreeNode* node, char* value)
{
    // when we reach a spot to put a node
    if (node == NULL) {
        return newNodeCreate(value);
    }

    // if the value is less than the key
    if (strcmp(value,node->key) < 0)
    {
        node->left = insertNode(node->left, value);
    }

    // if the value is greater than the key or equal to the key
    else if (strcmp(value, node->key) >= 0) {
        node->right = insertNode(node->right, value);
    } 
    return node;
}

// Function to perform pre-order traversal
void preOrder(struct BinaryTreeNode* root)
{
    if (root != NULL) {
        printf(" %s ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


struct BinaryTreeNode* buildBalancedBST(char **words, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    
    struct BinaryTreeNode* node = newNodeCreate(words[mid]);

    node->left = buildBalancedBST(words, start, mid - 1);
    node->right = buildBalancedBST(words, mid + 1, end);
    return node;
}

// Function to search for a value in the BST
struct BinaryTreeNode* searchBST(struct BinaryTreeNode *root, char* value) {
    // Base Cases: root is null or key is present at root
    if (root == NULL || strcmp(root->key, value) == 0)
       return root;

    // Key is greater than root's key
    if (strcmp(root->key, value) < 0)
       return searchBST(root->right, value);

    // Key is smaller than root's key
    return searchBST(root->left, value);
}


int searchDict(struct BinaryTreeNode *tree, char* word) 
{
    // Test Case MacDonald
    // check if the word matches exactly or the all caps version
    // must equal ::MacDonald or MACDONALD
    
    printf("\n\nSeach Dict:%s\n",word);
    if (searchBST(tree, word) != NULL)
    {
        printf("Found:1:%s\n", word);
        return 1;
    }
    // not found yet

    // check if the word is all caps
    // must equal ::MacDonald
    // given MACDONALD
    // if (searchBST(treeCaps, word) != NULL)
    // {
    //     printf("Found:2:%s\n", word);
    //     return 1;
    // }
    // int isAllCap = 1;
    // // check if word is all uppercase
    // for(int i = 0; word[i]; i++)
    // {
    //     if (islower(word[i]))
    //     {
    //         isAllCap = 0;
    //         printf("Is not all uppercase\n");
    //         break;
    //     }
    // }

    // // if it is all caps
    // if (isAllCap) 
    // {
    //     char tempWord[75];
    //     int i;
    //     for (i = 0; word[i]; i++) 
    //     {
    //         char chr = word[i]; 
    //         tempWord[i] = tolower(chr); 
    //     }
    //     tempWord[strlen(word)]='\0';
    //     printf("tempWord:2:%s\n",tempWord);
        
    //     // whole word is lowercase
    //     if (searchBST(tree, tempWord) != NULL)
    //     {
    //         printf("Found:2:%s\n", tempWord);
    //         return 1;
    //     }
    // }



    // check if word starts with an uppercase letter
    if (islower(word[0]))
    {
        char tempWord[75];
        int i;
        for (i = 0; word[i]; i++) 
        {
            char chr = word[i]; 
            if(i==0)
            {
                tempWord[i] = tolower(chr); 
            }
            else
            {
                tempWord[i] = chr;
            } 
        }
        // add the terminator string
        tempWord[strlen(word)]='\0';
        printf("tempWord:3:%s\n",tempWord);

        if (searchBST(tree, tempWord) != NULL)
        {
            printf("Found:3:%s\n", tempWord);
            return 1;
        }
    }

    printf("Not found:%s\n", word);
    return 0;

}