#include <stdio.h>
#include "binaryTree.h"

int main() {
    Dictionary *dictionary = createDictionary();
    addWord(dictionary, 8, "abcde");
    addWord(dictionary, 9, "abcdef");
    addWord(dictionary, 12, "abde");
    addWord(dictionary, 3, "abdedsgdsg");
    addWord(dictionary, 1, "abdefff");
    addWord(dictionary, 5, "abdddefff");
    addWord(dictionary, 4, "abdffefff");
    char* temp = getWord(dictionary, 1);
    bool check = isContain(dictionary,1);
    deleteTree(&dictionary);

    return 0;
}
