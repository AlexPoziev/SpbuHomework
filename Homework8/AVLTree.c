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

    // to ways
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

Node* insert(Node *node, int token, char *value, bool *isPart) {
    if (node == NULL) {
        Node *newNode = createNode(token, value);
        return newNode;
    }

    Direction direction = 0;

    if (token < node->token) {
        node->leftChild = insert(node->leftChild, token, value, isPart);
        direction = left;
    } else if (token > node->token) {
        node->rightChild = insert(node->rightChild, token, value, isPart);
        direction = right;
    } else {
        // case find existing token
        *isPart = true;
        char *newValue = calloc(strlen(value), sizeof(char));
        strcpy(newValue, value);
        free(node->value);
        node->value = newValue;
        return node;
    }

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

int addValue(Dictionary *dictionary, int token, char* value) {
    if (dictionary == NULL) {
        return 1;
    }
    if (dictionary->dictionary == NULL) {
        Node *newValue = createNode(token, value);
        dictionary->dictionary = newValue;

        return 0;
    }

    bool isPart = false;
    dictionary->dictionary = insert(dictionary->dictionary, token, value, &isPart);

    return 0;
}