#include "binaryTree.h"
#include <stdlib.h>

#define MAX_SIZE_NUMBER 10

// Здравствуйте. Могут быть и числа, даже отрицательные числа. Можно использовать sscanf или atoi для их разбора.
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

void fGetTreeRecursion(FILE *file, Node *node) {
    bool wasLeft = false;
    node->value = calloc(1, sizeof(char));
    if (node->value == NULL) {
        // добавить ерроркод
        return;
    }
    // get open parenthesis
    getc(file);
    // get operator
    node->value[0] = (char)getc(file);
    // get space
    getc(file);
    char next = (char)(getc(file));
    if (next == '(') {
        ungetc(next, file);
        Node *nextNode = malloc(sizeof(Node));
        node->leftChild = nextNode;
        fGetTreeRecursion(file, nextNode);
    } else {
        ungetc(next, file);
        char *newValue = calloc(MAX_SIZE_NUMBER, sizeof(char));
        if (newValue == NULL) {
            // добавить ерроркод
            return;
        }
        node->leftChild = malloc(sizeof(Node));
        if (node->leftChild == NULL) {
            // добавить ерроркод
            return;
        }
        node->leftChild->value = newValue;
        fscanf(file, "%s", node->leftChild->value);
    }
    getc(file);

    next = (char)(getc(file));
    if (next == '(') {
        ungetc(next, file);
        Node *nextNode = malloc(sizeof(Node));
        node->rightChild = nextNode;
        fGetTreeRecursion(file, nextNode);
    } else {
        ungetc(next, file);
        char *newValue = calloc(MAX_SIZE_NUMBER, sizeof(char));
        if (newValue == NULL) {
            // добавить ерроркод
            return;
        }
        node->rightChild = malloc(sizeof(Node));
        if (node->rightChild == NULL) {
            // добавить ерроркод
            return;
        }
        node->rightChild->value = newValue;
        fscanf(file, "%[^)]", node->rightChild->value);
        getc(file);
    }
}

Tree* fGetTree(FILE *file, char *fileName, Tree *tree) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }
    tree->root = malloc(sizeof(Node));
    fGetTreeRecursion(file, tree->root);

}