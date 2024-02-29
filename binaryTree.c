#include "binaryTree.h"

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
struct BinaryTreeNode* searchBST(struct BinaryTreeNode* root, char* value) {
    // Base Cases: root is null or key is present at root
    if (root == NULL || strcmp(root->key, value) == 0)
       return root;

    // Key is greater than root's key
    if (strcmp(root->key, value) < 0)
       return searchBST(root->right, value);

    // Key is smaller than root's key
    return searchBST(root->left, value);
}