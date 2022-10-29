#include "binaryTreeTest.h"
#include <stdlib.h>
#include <string.h>

bool createDictionaryTest(void) {
    Dictionary *dictionary = createDictionary();

    bool test = dictionary != NULL;

    deleteTree(&dictionary);

    return test;
}

bool addWordTest(void) {
    Dictionary *dictionary = createDictionary();
    int errorCode = 0;
    errorCode = addWord(dictionary, 10, "Osman");
    if (errorCode) {
        return false;
    }
    errorCode = addWord(dictionary, 100, "Commonwealth");
    if (errorCode) {
        return false;
    }

    errorCode = addWord(dictionary, 0, "Uther");
    if (errorCode) {
        return false;
    }

    bool firstTest = strcmp(getWord(dictionary, 10), "Osman");
    bool secondTest = strcmp(getWord(dictionary, 0), "Uther");
    bool thirdTest = strcmp(getWord(dictionary, 100), "Commonwealth");
    errorCode = addWord(dictionary, 0, "RIP");
    if (errorCode) {
        return false;
    }
    bool fourthTest = strcmp(getWord(dictionary, 0), "RIP");

    deleteTree(&dictionary);

    return !firstTest && !secondTest && !thirdTest && !fourthTest;
}