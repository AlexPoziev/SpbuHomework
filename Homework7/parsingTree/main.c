#include "binaryTree.h"
#include "testBinaryTree.h"
#include <stdio.h>

int main() {
    if (!deleteTreeTest() && !createTreeTest() && !calculateTreeTest() && !fileGetTreeTest()) {
        printf("Tests Failed");
        return 1;
    }

    printf("Input name of file with length less than 20: ");
    char fileName[20] = {0};
    scanf("%s", fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No file with this name");
        return 0;
    }

    fclose(file);

    Tree *tree = createTree();
    if (tree == NULL) {
        printf("Not enough memory");
        return 1;
    }

    int errorCode = fileGetTree(fileName, tree);
    if (errorCode == 1) {
        deleteTree(&tree);
        printf("Not enough memory");
        return 1;
    } else if (errorCode == -1) {
        deleteTree(&tree);
        printf("Tree doesnt exist");
        return -1;
    }

    printf("Tree: ");
    printTree(tree);

    printf("\nValue of tree is: %g", calculateTree(tree));

    deleteTree(&tree);

    return 0;
}
