#include "binaryTree.h"

#include <stdlib.h>
#include <string.h>

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
        nextNode = currentNode->token > token ? currentNode->leftChild : currentNode->rightChild;
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
        char *newWord = calloc(strlen(word), sizeof(char));
        stpcpy(newWord, word);
        dictionary->root->word = newWord;

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
    char *newWord = calloc(strlen(word), sizeof(char));
    stpcpy(newWord, word);
    newNode->word = newWord;
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

// get most right of left children
Node* getMostRight(Node* root) {
    Node *currentNode = root->leftChild;
    Node *next = currentNode->rightChild;
    while (next != NULL) {
        currentNode = next;
        next = currentNode->rightChild;
    }

    return currentNode;
}

int deleteWord(Dictionary *dictionary, int token) {
    if (dictionary == NULL) {
        return 1;
    }

    bool isEnd = false;
    Node *currentNode = findPosition(dictionary, token, &isEnd);
    if (isEnd) {
        return 0;
    }
    // childfree case
    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL) {
        currentNode->parent->token > token
        ? (currentNode->parent->leftChild = NULL)
        : (currentNode->parent->rightChild = NULL);

        free(currentNode->word);
        free(currentNode);

        return 0;
    }
    // case only child
    if (currentNode->leftChild == NULL || currentNode->rightChild == NULL) {
        Node *temp = currentNode->leftChild == NULL ? currentNode->rightChild : currentNode->leftChild;
        temp->parent = currentNode->parent;
        currentNode->parent->token > token
        ? (currentNode->parent->leftChild = temp)
        : (currentNode->parent->rightChild = temp);

        free(currentNode->word);
        free(currentNode);

        return 0;
    }
    // case two children
    Node *mostRight = getMostRight(currentNode);
    currentNode->token = mostRight->token;
    free(currentNode->word);
    currentNode->word = mostRight->word;
    if (mostRight->leftChild != NULL) {
        mostRight->leftChild->parent = mostRight->parent;
    }
    mostRight->parent->rightChild = mostRight->leftChild;

    free(mostRight);

    return 0;
}

void deleteTreeRecursion(Node *child) {
    if (child == NULL) {
        return;
    }

    deleteTreeRecursion(child->leftChild);
    deleteTreeRecursion(child->rightChild);

    free(child->word);
    child->word = NULL;
    free(child);
    child = NULL;
}

void deleteTree(Dictionary **dictionary) {
    deleteTreeRecursion((*dictionary)->root);

    free(*dictionary);
    *dictionary = NULL;
}