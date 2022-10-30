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
    node = malloc(sizeof(Node));
    if (node == NULL) {
        // добавить ерроркод
        return
    }
    node->value = calloc(1, sizeof(char));
    
}

Tree* fGetTree(FILE *file, char *fileName, Tree *tree) {
    file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }

}