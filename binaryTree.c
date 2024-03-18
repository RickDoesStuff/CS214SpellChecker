#include "binaryTree.h"
#include <ctype.h>

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


int searchDict(struct BinaryTreeNode *tree, struct BinaryTreeNode *treeCaps, char* word) 
{
    // the word matches exactly either the normal or caps tree
    if (matchTree(tree,treeCaps,word) == 1){
        // it matches
        return 1;
    }

    // check if the first letter of the word is uppercase but the correct spelling is the first word being lowercase
    // typically for beginning of sentences
    if (checkUppercase(tree,treeCaps,word) == 1){
        return 1;
    }

    //check if word is hypenated
    if (searchHyphenatedWord(tree,treeCaps,word) == 1)
    {
        return 1;
    }
    //printf("Not found:%s\n", word);
    return 0;

}

int searchPartOfHyphenWord(struct BinaryTreeNode *tree, struct BinaryTreeNode *treeCaps, char* word) {
    // the word matches exactly either the normal or caps tree
    if (matchTree(tree,treeCaps,word) == 1){
        // it matches
        return 1;
    }

    // check if the first letter of the word is uppercase but the correct spelling is the first word being lowercase
    // typically for beginning of sentences
    if (checkUppercase(tree,treeCaps,word) == 1){
        return 1;
    }
    return 0;
}

/**
 * check if word starts with an uppercase letter
 * if it is uppercase, make it lowercase 
*/
int checkUppercase(struct BinaryTreeNode *tree, struct BinaryTreeNode *treeCaps, char *word)
{
    //printf("upperCase?:%c\n",word[0]);
    if (isupper(word[0]))
    {
        char tempWord[4096];
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
        //printf("Test 2:Checking tempWord:%s:from:%s\n",tempWord,word);

        if (searchBST(tree, tempWord) != NULL)
        {
            //printf("Test 2:Found tempword:%s:from:%s\n", tempWord,word);
            return 1;
        }
    }
    //printf("Test 2:not found:%s\n",word);
    return 0;
}

/**
 * Word must match the normal or caps tree exactly
*/
int matchTree(struct BinaryTreeNode *tree, struct BinaryTreeNode *treeCaps, char *word) 
{
// Test Case MacDonald
    // check if the word matches exactly or the all caps version
    // must equal ::MacDonald or MACDONALD
    
    //printf("\n\nSeach Dict:%s\n",word);
    if (searchBST(tree, word) != NULL)
    {
        //printf("Test 1:Found:%s\n", word);
        return 1;
    }
    //printf("Test 1:Not found:%s\n",word);
    // not found yet

    // check if the word is all caps
    // must equal ::MacDonald
    // given MACDONALD
    if (searchBST(treeCaps, word) != NULL)
    {
        //printf("Test 1 CAPS:Found:%s\n", word);
        return 1;
    }
    //printf("Test 1 CAPS:Not found:%s\n",word);
    return 0;
}

/**
 * 
*/
int searchHyphenatedWord(struct BinaryTreeNode *tree, struct BinaryTreeNode *treeCaps, char *word) 
{
    int endOfWordIndex = 0;
    int startOfWordIndex = 0;
    int wordLength = 0;
    int hadHyphen = 0;
    //int length = strlen(word);
    char tempWord[4096];

    int i = 0;
    for (i = 0; word[i]; i++) 
    {   
        // check if the current char is a hyphen or the next char is a null terminator
        // because if the next letter is a null terminator we need to check the current word since its the end of the entire word
        if(word[i] == '-' || (hadHyphen==1 && word[i+1] == '\0')) {
            // end the first part of the hyphenated word
            endOfWordIndex = i;
            // get the length of the word in the hyphenated word
            if (word[i] == '-') 
            {
                hadHyphen = 1;
                // for the hyphen
                wordLength = endOfWordIndex - startOfWordIndex;
            }else{
                // for the end of the word
                wordLength = endOfWordIndex - startOfWordIndex + 1;
            }

            // take part of the word and put it into temp word
            strncpy(tempWord,&word[startOfWordIndex], wordLength);

            // put null terminator at end of word
            tempWord[wordLength] = '\0'; 

            //printf("tempWord:%s\n",tempWord);

            // if not found, exit
            if (searchPartOfHyphenWord(tree, treeCaps, tempWord) == 0)
            {                
                //printf("Test 3:not found tempWord:%s\n",tempWord);
                return 0;
            }
            
            // if we are at the end of the entire word, break
            if (word[i+1] == '\0') {
                break;
            }
            // move to the start of the next segment after the hypen
            startOfWordIndex = i + 1; 
            
        }
    }

    // the word ends with a -
    if (wordLength==0)
    {
        //printf("word length:%i\n",wordLength);
        return 0;
    }
    //printf("\n**Test 3:Found word:%s\n",word);
    return 1;
}
