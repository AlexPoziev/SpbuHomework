#include "binaryTreeTest.h"
#include <string.h>

bool createDictionaryTest(void) {
    Dictionary *dictionary = createDictionary();

    bool test = dictionary != NULL;

    deleteTree(&dictionary);

    return test;
}

bool deleteTreeTest(void) {
    Dictionary *dictionary = createDictionary();
    int errorCode = 0;
    errorCode = addWord(dictionary, 10, "ParahodEntertainment");
    if (errorCode) {
        return false;
    }
    errorCode = addWord(dictionary, 100, "Jaina");
    if (errorCode) {
        return false;
    }

    deleteTree(&dictionary);

    return dictionary == NULL;
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
    char *test = getWord(dictionary, 0);
    bool fourthTest = strcmp(getWord(dictionary, 0), "RIP");

    deleteTree(&dictionary);

    return !firstTest && !secondTest && !thirdTest && !fourthTest;
}

bool getWordTest(void) {
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

    bool firstTest = strcmp(getWord(dictionary, 10), "Osman");
    bool secondTest = strcmp(getWord(dictionary, 100), "Commonwealth");
    bool thirdTest = getWord(dictionary, 0) == NULL;

    deleteTree(&dictionary);

    return !firstTest && !secondTest && thirdTest;
}

bool deleteWordTest(void) {
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
    errorCode = addWord(dictionary, 3, "Uther");
    if (errorCode) {
        return false;
    }
    errorCode = addWord(dictionary, 0, "Scorch");
    if (errorCode) {
        return false;
    }

    deleteWord(dictionary, 10);
    bool firstTest = !isContain(dictionary, 10);
    deleteWord(dictionary, 0);
    bool secondTest = !isContain(dictionary, 0);
    bool thirdTest = isContain(dictionary, 100);
    bool fourthTest = isContain(dictionary, 3);

    deleteTree(&dictionary);

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool isContainTest(void) {
    Dictionary *dictionary = createDictionary();
    int errorCode = 0;
    errorCode = addWord(dictionary, 10, "ParahodEntertainment");
    if (errorCode) {
        return false;
    }
    errorCode = addWord(dictionary, 100, "Jaina");
    if (errorCode) {
        return false;
    }

    bool firstTest = isContain(dictionary, 10);
    bool secondTest = isContain(dictionary, 100);
    bool thirdTest = !isContain(dictionary, 0);
    deleteWord(dictionary, 100);
    bool fourthTest = !isContain(dictionary, 100);

    deleteTree(&dictionary);

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool fullTest(void) {
    return createDictionaryTest() && deleteWordTest() && deleteTreeTest()
    && addWordTest() && isContainTest() && getWordTest();
}