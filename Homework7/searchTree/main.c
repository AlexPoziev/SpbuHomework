#include <stdio.h>
#include "binaryTree.h"

int main() {
    Dictionary *dictionary = createDictionary();
    addWord(dictionary, 1, "abcde");
    addWord(dictionary, 0, "abcdef");
    addWord(dictionary, 2, "abde");
    char* temp = getWord(dictionary, 1);
    bool check = isContain(dictionary,1);
    deleteWord(dictionary, 2);

    return 0;
}
