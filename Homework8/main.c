#include <stdio.h>
#include "AVLTree.h"

int main() {
    Dictionary *dictionary = createDictionary();
    addValue(dictionary, 1, "gg");
    addValue(dictionary, 2, "check");
    addValue(dictionary, 4, "ttet");
    addValue(dictionary, 5, "ttfet");

    deleteWord(dictionary, 2);
    deleteWord(dictionary,4);
    deleteWord(dictionary, 5);
    deleteWord(dictionary, 1);
    return 0;
}


