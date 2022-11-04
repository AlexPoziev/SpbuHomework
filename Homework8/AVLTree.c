#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char *value;
    int token;
    int height;
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

int getHeight(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

Node* rotateLeft(Node *currentNode) {
    Node *rightChild = currentNode->rightChild;
    Node *leftGrandson = rightChild->leftChild;

    rightChild->leftChild = currentNode;
    currentNode->rightChild = leftGrandson;

    currentNode->balance = getBalance(currentNode->rightChild) - getBalance(currentNode->leftChild);
    rightChild->balance = getBalance(rightChild->rightChild) - getBalance(rightChild->leftChild);

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

    currentNode->balance = getBalance(currentNode->rightChild) - getBalance(currentNode->leftChild);
    rightChild->balance = getBalance(rightChild->rightChild) - getBalance(rightChild->leftChild);
    leftGrandson->balance = getBalance(leftGrandson->rightChild) - getBalance(leftGrandson->leftChild);

    return leftGrandson;
}

Node* rotateRight(Node *currentNode) {
    Node *leftChild = currentNode->leftChild;
    Node *rightGrandson = leftChild->rightChild;

    leftChild->rightChild = currentNode;
    currentNode->leftChild = rightGrandson;

    currentNode->balance = getBalance(currentNode->rightChild) - getBalance(currentNode->leftChild);
    leftChild->balance = getBalance(leftChild->rightChild) - getBalance(leftChild->leftChild);

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

    currentNode->balance = getBalance(currentNode->rightChild) - getBalance(currentNode->leftChild);
    leftChild->balance = getBalance(leftChild->rightChild) - getBalance(leftChild->leftChild);
    rightGrandson->balance = getBalance(rightGrandson->rightChild) - getBalance(rightGrandson->leftChild);

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

Node* insert(Node *node, int token, char *value, bool *isPart, int *heightDifference) {
    if (node == NULL) {
        Node *newNode = createNode(token, value);
        return newNode;
    }

    Direction direction = 0;
    if (token < node->token) {
        node->leftChild = insert(node->leftChild, token, value, isPart, heightDifference);
        direction = left;
    } else if (token > node->token) {
        node->rightChild = insert(node->rightChild, token, value, isPart, heightDifference);
        direction = right;
    } else {
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
    node->balance += direction;
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