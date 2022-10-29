#include <stdio.h>
#include "binaryTree.h"
#include "binaryTreeTest.h"

int main() {
    if (!createDictionaryTest()) {
        printf("Tests Failed");
        return 1;
    }
    Dictionary *dictionary = createDictionary();
    addWord(dictionary, 8, "abcde");
    addWord(dictionary, 9, "abcdef");
    addWord(dictionary, 12, "abde");
    addWord(dictionary, 12, "abdefffffff");
    char* temp = getWord(dictionary, 1);
    bool check = isContain(dictionary,1);

    return 0;
}
