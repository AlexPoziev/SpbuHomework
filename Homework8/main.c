#include <stdio.h>
#include "AVLTree.h"

int main() {
    Dictionary *dictionary = createDictionary();
    addValue(dictionary, 1, "gg");
    addValue(dictionary, 22, "check");
    addValue(dictionary, 53, "ttet");
    addValue(dictionary, 81, "tetetet");
    addValue(dictionary, 94, "tetet");
    addValue(dictionary, 37, "tet");
    addValue(dictionary, 95, "tet");



    return 0;
}
