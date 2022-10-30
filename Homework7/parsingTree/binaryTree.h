#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct Tree Tree;

// allocate memory for Tree. Returns 1 if not enough memory, and 0 if all ok
Tree* createTree(void);

// build binary tree from file data
int fGetTree(FILE *file, char *fileName, Tree *tree);
