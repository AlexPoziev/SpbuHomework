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

Node* rotateBigLeft(Node* currentNode) {
    Node *rightChild = currentNode->rightChild;
    Node *leftGrandson = rightChild->leftChild;
    Node *leftGrandGrandson = leftGrandson->leftChild;
    Node *rightGrandGrandson = leftGrandson->rightChild;

    leftGrandson->leftChild = currentNode;
    leftGrandson->rightChild = rightChild;
    currentNode->rightChild = leftGrandGrandson;
    rightChild->leftChild = rightGrandGrandson;

    return leftGrandson;
}

Node* rotateRight(Node *currentNode) {
    Node *leftChild = currentNode->leftChild;
    Node *rightGrandson = leftChild->rightChild;

    leftChild->rightChild = currentNode;
    currentNode->leftChild = rightGrandson;

    return leftChild;
}

Node* rotateBigRight(Node* currentNode) {
    Node *leftChild = currentNode->leftChild;
    Node *rightGrandson = leftChild->rightChild;
    Node *rightGrandGrandson = rightGrandson->rightChild;
    Node *leftGrandGrandson = rightGrandson->leftChild;

    rightGrandson->rightChild = currentNode;
    rightGrandson->leftChild = leftChild;
    currentNode->leftChild = rightGrandGrandson;
    leftChild->rightChild = leftGrandGrandson;

    return rightGrandson;
}