#include "binaryTree.h"
#include <stdlib.h>

#define MAX_SIZE_NUMBER 10

typedef struct Node {
    char *value;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

typedef struct Tree {
    Node *root;
} Tree;

Tree* createTree(void) {
    Tree *temp = malloc(sizeof(Tree));
    temp->root = NULL;

    return temp;
}

int fileGetTreeRecursion(FILE *file, Node *node) {
    int errorCode = 0;

    node->value = calloc(1, sizeof(char));
    if (node->value == NULL) {
        return 1;
    }
    // skip open parenthesis
    getc(file);
    // get operator
    node->value[0] = (char)getc(file);
    // skip space
    getc(file);
    char next = (char)(getc(file));
    if (next == '(') {
        ungetc(next, file);
        Node *nextNode = malloc(sizeof(Node));
        node->leftChild = nextNode;
        errorCode = fGetTreeRecursion(file, nextNode);
        if (errorCode) {
            return 1;
        }
    } else {
        ungetc(next, file);
        char *newValue = calloc(MAX_SIZE_NUMBER, sizeof(char));
        if (newValue == NULL) {
            return 1;
        }
        node->leftChild = malloc(sizeof(Node));
        if (node->leftChild == NULL) {
            return 1;
        }
        node->leftChild->value = newValue;
        fscanf(file, "%s", node->leftChild->value);
    }
    // skip space
    getc(file);

    next = (char)(getc(file));
    if (next == '(') {
        ungetc(next, file);
        Node *nextNode = malloc(sizeof(Node));
        node->rightChild = nextNode;
        errorCode = fGetTreeRecursion(file, nextNode);
        if (errorCode) {
            return 1;
        }
    } else {
        ungetc(next, file);
        char *newValue = calloc(MAX_SIZE_NUMBER, sizeof(char));
        if (newValue == NULL) {
            return 1;
        }
        node->rightChild = malloc(sizeof(Node));
        if (node->rightChild == NULL) {
            return 1;
        }
        node->rightChild->value = newValue;
        fscanf(file, "%[^)]", node->rightChild->value);
        getc(file);
    }

    return 0;
}

int fileGetTree(FILE *file, char *fileName, Tree *tree) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        return -1;
    }

    tree->root = malloc(sizeof(Node));
    if (tree->root == NULL) {
        return 1;
    }

    int errorCode = fGetTreeRecursion(file, tree->root);
    if (errorCode == 1) {
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}