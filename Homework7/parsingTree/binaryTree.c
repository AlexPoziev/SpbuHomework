#include "binaryTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    Tree *temp = calloc(1, sizeof(Tree));

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
        errorCode = fileGetTreeRecursion(file, nextNode);
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
        errorCode = fileGetTreeRecursion(file, nextNode);
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

int fileGetTree(char *fileName, Tree *tree) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return -1;
    }

    tree->root = malloc(sizeof(Node));
    if (tree->root == NULL) {
        fclose(file);
        return 1;
    }

    int errorCode = fileGetTreeRecursion(file, tree->root);
    if (errorCode == 1) {
        deleteTree(&tree);
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}

bool isOperator(char *string) {
    return !strcmp("+", string) || !strcmp("-", string) || !strcmp("/", string) || !strcmp("*", string);
}

void deleteTreeRecursion(Node *child) {
    if (child == NULL) {
        return;
    }

    deleteTreeRecursion(child->leftChild);
    deleteTreeRecursion(child->rightChild);

    free(child->value);
    free(child);
}

void deleteTree(Tree **tree) {
    if (tree == NULL || *tree == NULL) {
        return;
    }

    deleteTreeRecursion((*tree)->root);

    free(*tree);
    *tree = NULL;
}

void printTreeRecursion(Node *child) {
    if (child == NULL) {
        return;
    }
    if (!isOperator(child->value)) {
        printf(" %s", child->value);
        return;
    }

    printf(" (%s", child->value);
    printTreeRecursion(child->leftChild);
    printTreeRecursion(child->rightChild);
    printf(")");
}

int printTree(Tree *tree) {
    if (tree == NULL) {
        return 1;
    }

    printTreeRecursion(tree->root);

    return 0;
}

double operations(double firstNumber, double secondNumber, char operation) {
    switch (operation) {
        case '*': {
            return firstNumber * secondNumber;
        }
        case '-': {
            return secondNumber - firstNumber;
        }
        case '+': {
            return firstNumber + secondNumber;
        }
        case '/': {
            return secondNumber / firstNumber;
        }
        default: {
            return 0;
        }
    }
}

double calculateTreeRecursion(Node *root) {
    if (!isOperator(root->value)) {
        return atoi(root->value);
    }

    return operations(calculateTreeRecursion(root->leftChild),
                      calculateTreeRecursion(root->rightChild), root->value[0]);
}

double calculateTree(Tree *tree) {
    return calculateTreeRecursion(tree->root);
}

bool isRootEmpty(Tree *tree) {
    return tree->root == NULL;
}