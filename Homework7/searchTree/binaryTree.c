#include "binaryTree.h"

#include <stdlib.h>

typedef struct Node {
    int token;
    char *word;
    struct Node* leftChild;
    struct Node* rightChild;
    struct Node* parent;
} Node;

typedef struct Dictionary {
    Node *root;
} Dictionary;

Dictionary* createDictionary(void) {
    Dictionary *temp = malloc(sizeof(Dictionary));
    temp->root = NULL;
    return temp;
}

Node* findPosition(Dictionary *dictionary, int token, bool *isEnd) {
    Node *currentNode = dictionary->root;
    if (currentNode->token == token) {
        *isEnd = false;
        return currentNode;
    }
    Node *nextNode = currentNode->token > token ? currentNode->leftChild : currentNode->rightChild;
    while (nextNode != NULL) {
        currentNode = nextNode;
        if (currentNode->token == token) {
            *isEnd = false;
            return currentNode;
        }
        nextNode = currentNode->token < token ? currentNode->leftChild : currentNode->rightChild;
    }

    *isEnd = true;
    return currentNode;
}

int addWord(Dictionary *dictionary, int token, char* word) {
    if (dictionary == NULL || word == NULL) {
        return 1;
    }

    if (dictionary->root == NULL) {
        dictionary->root = malloc(sizeof(Node));
        if (dictionary->root == NULL) {
            return 1;
        }
        dictionary->root->leftChild = NULL;
        dictionary->root->rightChild = NULL;
        dictionary->root->parent = NULL;
        dictionary->root->token = token;
        dictionary->root->word = word;

        return 0;
    }

    bool isEnd = false;
    Node *currentNode = findPosition(dictionary, token, &isEnd);
    if (isEnd == false) {
        free(currentNode->word);
        currentNode->word = word;

        return 0;
    }
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return 1;
    }
    newNode->parent = currentNode;
    newNode->token = token;
    newNode->word = word;
    newNode->rightChild = NULL;
    newNode->leftChild = NULL;

    newNode->token < currentNode->token
    ? (currentNode->leftChild = newNode)
    : (currentNode->rightChild = newNode);

    return 0;
}

char* getWord(Dictionary *dictionary, int token) {
    if (dictionary == NULL) {
        return NULL;
    }
    bool isEnd = false;
    Node *currentNode = findPosition(dictionary, token, &isEnd);
    return isEnd ? NULL : currentNode->word;
}

bool isContain(Dictionary *dictionary, int token) {
    if (dictionary == NULL) {
        return false;
    }
    bool isEnd = false;
    findPosition(dictionary, token, &isEnd);

    return !isEnd;
}