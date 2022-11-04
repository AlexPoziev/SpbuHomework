#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char *value;
    int token;
    int balance;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

typedef struct Dictionary {
    Node *head;
};

typedef enum Direction{
    left,
    right
} Direction;

Dictionary* createDictionary(void) {
    Dictionary *newDictionary = malloc(sizeof(Dictionary));
    newDictionary->head = NULL;
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

Node* rotateLeft(Node *currentNode) {
    Node *rightChild = currentNode->rightChild;
    Node *leftGrandson = rightChild->leftChild;

    rightChild->leftChild = currentNode;
    currentNode->rightChild = leftGrandson;

    return rightChild;
}

Node* rotateRight(Node *currentNode) {
    Node *leftChild = currentNode->leftChild;
    Node *rightGrandson = leftChild->rightChild;

    leftChild->rightChild = currentNode;
    currentNode->leftChild = rightGrandson;

    return leftChild;
}