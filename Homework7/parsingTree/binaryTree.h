#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct Tree Tree;

// allocate memory for Tree. Returns 1 if not enough memory, and 0 if all ok
Tree* createTree(void);

// build binary tree from file data
int fileGetTree(FILE *file, char *fileName, Tree *tree);

// deallocate memory for binaryTree
void deleteTree(Tree **tree);

// print tree to console. Return 1 if tree doesn't exist
int printTree(Tree *tree);

// calculate value of expression in tree
double calculateTree(Tree *tree);

// check is root empty
bool isRootEmpty(Tree *tree);