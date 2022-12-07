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
    Dictionary *temp = calloc(1, sizeof(Dictionary));
    return temp;
}

Node* findPosition(Dictionary *dictionary, int token, bool *isEnd) {
    Node *currentNode = dictionary->root;
    if (currentNode == NULL) {
        *isEnd = true;
        return NULL;
    }
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
        dictionary->root = calloc(sizeof(Node));
        if (dictionary->root == NULL) {
            return 1;
        }

        dictionary->root->token = token;
        char *newWord = calloc(strlen(word), sizeof(char));
        if (newWord == NULL) {
            return 1;
        }

        stpcpy(newWord, word);
        dictionary->root->word = newWord;

        return 0;
    }

    bool isEnd = false;
    Node *currentNode = findPosition(dictionary, token, &isEnd);

    char *newWord = calloc(strlen(word), sizeof(char));
    if (newWord == NULL) {
        return 1;
    }

    // if found same token
    if (isEnd == false) {
        free(currentNode->word);
        currentNode->word = newWord;

        return 0;
    }

    stpcpy(newWord, word);

    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        free(newWord);
        return 1;
    }

    // if new token
    newNode->parent = currentNode;
    newNode->token = token;
    newNode->word = newWord;

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
        if (currentNode->parent == NULL) {
            free(currentNode->word);
            free(currentNode);
            dictionary->root = NULL;

            return 0;
        }

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
        if (currentNode->parent == NULL) {
            dictionary->root = temp;
            free(currentNode->word);
            free(currentNode);

            return 0;
        }

        temp->parent = currentNode->parent;
        currentNode->parent->token > token
        ? (currentNode->parent->leftChild = temp)
        : (currentNode->parent->rightChild = temp);

        free(currentNode->word);
        free(currentNode);

        return 0;
    }
    // case two children
    Node *mostLeftRight = getMostRight(currentNode);
    currentNode->token = mostLeftRight->token;
    free(currentNode->word);
    currentNode->word = mostLeftRight->word;
    if (mostLeftRight->leftChild != NULL) {
        mostLeftRight->leftChild->parent = mostLeftRight->parent;
    }

    // case if most right is first right child of current
    mostLeftRight->parent != currentNode
    ? (mostLeftRight->parent->rightChild = mostLeftRight->leftChild)
    : (mostLeftRight->parent->leftChild = mostLeftRight->leftChild);

    free(mostLeftRight);

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