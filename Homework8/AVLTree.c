#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *value;
    int token;
    int8_t balance;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

typedef struct Dictionary {
    Node *dictionary;
} Dictionary;

typedef enum Direction{
    left = -1,
    right = 1
} Direction;

Dictionary* createDictionary(void) {
    Dictionary *newDictionary = malloc(sizeof(Dictionary));
    newDictionary->dictionary = NULL;
    return newDictionary;
}

Node* createNode(int token, char *value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->token = token;
    char *newValue = calloc(strlen(value), sizeof(char));
    stpcpy(newValue, value);
    newNode->value = newValue;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->balance = 0;

    return newNode;
}

int8_t getBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->balance;
}

Node* rotateLeft(Node *currentNode) {
    Node *rightChild = currentNode->rightChild;
    Node *leftGrandson = rightChild->leftChild;

    rightChild->leftChild = currentNode;
    currentNode->rightChild = leftGrandson;

    // two ways
    if (rightChild->balance) {
        currentNode->balance = 0;
        rightChild->balance = 0;
    } else {
        currentNode->balance = 1;
        rightChild->balance = -1;
    }

    return rightChild;
}

Node* bigRotateLeft(Node* currentNode) {
    Node *rightChild = currentNode->rightChild;
    Node *leftGrandson = rightChild->leftChild;
    Node *leftGrandGrandson = leftGrandson->leftChild;
    Node *rightGrandGrandson = leftGrandson->rightChild;

    leftGrandson->leftChild = currentNode;
    leftGrandson->rightChild = rightChild;
    currentNode->rightChild = leftGrandGrandson;
    rightChild->leftChild = rightGrandGrandson;

    switch (leftGrandson->balance) {
        case -1: {
            currentNode->balance = 0;
            rightChild->balance = 1;
            break;
        }
        case 0: {
            currentNode->balance = 0;
            rightChild->balance = 0;
            break;
        }
        case 1: {
            currentNode->balance =-1;
            rightChild->balance = 0;
            break;
        }
    }
    leftGrandson->balance = 0;

    return leftGrandson;
}

Node* rotateRight(Node *currentNode) {
    Node *leftChild = currentNode->leftChild;
    Node *rightGrandson = leftChild->rightChild;

    leftChild->rightChild = currentNode;
    currentNode->leftChild = rightGrandson;

    // two ways
    if (leftChild->balance) {
        currentNode->balance = 0;
        leftChild->balance = 0;
    } else {
        currentNode->balance = -1;
        leftChild->balance = 1;
    }

    return leftChild;
}

Node* bigRotateRight(Node* currentNode) {
    Node *leftChild = currentNode->leftChild;
    Node *rightGrandson = leftChild->rightChild;
    Node *rightGrandGrandson = rightGrandson->rightChild;
    Node *leftGrandGrandson = rightGrandson->leftChild;

    rightGrandson->rightChild = currentNode;
    rightGrandson->leftChild = leftChild;
    currentNode->leftChild = rightGrandGrandson;
    leftChild->rightChild = leftGrandGrandson;

    switch (rightGrandson->balance) {
        case -1: {
            currentNode->balance = -1;
            leftChild->balance = 0;
            break;
        }
        case 0: {
            currentNode->balance = 0;
            leftChild->balance = 0;
            break;
        }
        case 1: {
            currentNode->balance =0;
            leftChild->balance = 1;
            break;
        }
    }
    rightGrandson->balance = 0;

    return rightGrandson;
}

Node* balance(Node *node) {
    if (node->balance == 2) {
        if (node->rightChild->balance >= 0) {
            return rotateLeft(node);
        }
        return bigRotateLeft(node);
    }
    if (node->balance == -2) {
        if (node->leftChild->balance <= 0){
            return rotateRight(node);
        }
        return bigRotateRight(node);
    }

    return node;
}

Node* insert(Node *node, int token, char *value, bool *isPart, int8_t *errorCode) {
    // create leaf
    if (node == NULL) {
        Node *newNode = createNode(token, value);
        if (newNode == NULL) {
            *errorCode = 1;
            *isPart = true;
            return NULL;
        }
        return newNode;
    }

    Direction direction = 0;

    if (token < node->token) {
        node->leftChild = insert(node->leftChild, token, value, isPart, errorCode);
        direction = left;
    } else if (token > node->token) {
        node->rightChild = insert(node->rightChild, token, value, isPart, errorCode);
        direction = right;
    } else {
        // case finding existing token
        *isPart = true;
        char *newValue = calloc(strlen(value), sizeof(char));
        if (newValue == NULL) {
            *errorCode = 1;
        } else {
            strcpy(newValue, value);
            free(node->value);
            node->value = newValue;
            return node;
        }
    }

    // firstly was way to get from recursion without changing balance for create leaf case
    // now just general way to skip recursion
    if (*isPart) {
        return node;
    }

    node->balance = (int8_t)(node->balance + direction);
    // if -2 or 2 no more changes in balance in recursive calls
    // if 0 that means token get position of second child and if before it was ok, its will be ok after that :)
    if (node->balance == 2 || node->balance == -2 || node->balance == 0) {
        *isPart = true;
    }
    return balance(node);
}

// just a shell, call insert function, that really adds values
int addValue(Dictionary *dictionary, int token, char* value) {
    if (dictionary == NULL) {
        return -1;
    }
    if (dictionary->dictionary == NULL) {
        Node *newValue = createNode(token, value);
        dictionary->dictionary = newValue;

        return 0;
    }

    bool isPart = false;
    int8_t errorCode = 0;
    dictionary->dictionary = insert(dictionary->dictionary, token, value, &isPart, &errorCode);

    return errorCode;
}