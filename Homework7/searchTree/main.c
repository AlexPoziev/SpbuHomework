#include <stdio.h>
#include "binaryTree.h"

int main() {
    Dictionary *dictionary = createDictionary();
    addWord(dictionary, 1, "abcde");
    addWord(dictionary, 0, "abcdef");
    addWord(dictionary, 2, "abde");

    return 0;
}
