#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

void test(FILE *file) {
    char c = getc(file);
    c = getc(file);
    if (c == 'c') {
        ungetc('c', file);
    }
}

int main() {
    FILE *file = fopen("test.txt", "r");
    Tree *tree = createTree();
    int errorCode = fileGetTree(file, "test.txt", tree);

    printf("%g", calculateTree(tree));

    return 0;
}
