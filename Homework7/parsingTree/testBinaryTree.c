#include "binaryTree.h"
#include "testBinaryTree.h"
#include <stdio.h>

bool createTreeTest(void) {
    Tree *tree = createTree();

    bool test = tree != NULL;

    deleteTree(&tree);

    return test;
}

bool calculateTreeTest(void) {
    Tree *firstTree = createTree();
    int errorCode = fileGetTree("testFirst.txt", firstTree);
    if (errorCode) {
        return false;
    }
    const double delta = 0.00001;
    bool firstTest = (1.71429 - calculateTree(firstTree)) < delta;

    Tree *secondTree = createTree();
    errorCode = fileGetTree("testSecond.txt", secondTree);
    if (errorCode) {
        return false;
    }
    bool secondTest = 4 == calculateTree(secondTree);

    deleteTree(&firstTree);

    deleteTree(&secondTree);

    return secondTest && firstTest;
}

bool deleteTreeTest(void) {
    Tree *tree = createTree();
    fileGetTree("testSecond.txt", tree);

    deleteTree(&tree);

    bool test = tree == NULL;

    return test;
}

bool fileGetTreeTest(void) {
    Tree *treeTest = createTree();
    int errorCode = fileGetTree("testSecond.txt", treeTest);
    if (errorCode) {
        return false;
    }

    bool test = !isRootEmpty(treeTest);

    deleteTree(&treeTest);

    return test;
}

bool fullTest(void) {
    bool test = fileGetTreeTest() && createTreeTest() && calculateTreeTest() && deleteTreeTest();
}