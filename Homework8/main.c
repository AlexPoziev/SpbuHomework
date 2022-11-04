#include <stdio.h>
#include "AVLTree.h"

int main() {
    Dictionary *dictionary = createDictionary();
    addValue(dictionary, 9, "gg");
    addValue(dictionary, 8, "check");
    addValue(dictionary, 7, "ttet");
    addValue(dictionary, 6, "tetetet");
    addValue(dictionary, 5, "tetet");
    addValue(dictionary, 4, "tete44t");
    addValue(dictionary, 3, "tete43t");
    addValue(dictionary, 2, "te3t");
    addValue(dictionary, 1, "te3t");

    return 0;
}
