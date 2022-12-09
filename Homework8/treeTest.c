#include "treeTest.h"
#include "AVLTree.h"
#include <string.h>

bool createDictionaryTest(void) {
    Dictionary *dictionary = createDictionary();

    bool test = dictionary != NULL;

    deleteTree(&dictionary);

    return test;
}

bool deleteTreeTest(void) {
    Dictionary *dictionary = createDictionary();
    int errorCode = addValue(dictionary, "a", "ParahodEntertainment");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }

    errorCode = addValue(dictionary, "b", "Jaina");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }

    deleteTree(&dictionary);

    return dictionary == NULL;
}

bool addWordTest(void) {
    Dictionary *dictionary = createDictionary();
    int errorCode = addValue(dictionary, "a", "Osman");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }
    errorCode = addValue(dictionary, "b", "Commonwealth");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }
    errorCode = addValue(dictionary, "0", "Uther");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }

    bool firstTest = strcmp(getValue(dictionary, "a"), "Osman");
    bool secondTest = strcmp(getValue(dictionary, "0"), "Uther");
    bool thirdTest = strcmp(getValue(dictionary, "b"), "Commonwealth");
    errorCode = addValue(dictionary, "0", "RIP");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }

    bool fourthTest = strcmp(getValue(dictionary, "0"), "RIP");

    deleteTree(&dictionary);

    return !firstTest && !secondTest && !thirdTest && !fourthTest;
}

bool getWordTest(void) {
    Dictionary *dictionary = createDictionary();
    int errorCode = addValue(dictionary, "a", "Osman");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }
    errorCode = addValue(dictionary, "b", "Commonwealth");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }

    bool firstTest = strcmp(getValue(dictionary, "a"), "Osman");
    bool secondTest = strcmp(getValue(dictionary, "b"), "Commonwealth");
    deleteValue(dictionary, "a");
    bool thirdTest = getValue(dictionary, "a") == NULL;

    deleteTree(&dictionary);

    return !firstTest && !secondTest && thirdTest;
}

bool deleteWordTest(void) {
    Dictionary *dictionary = createDictionary();
    int errorCode = addValue(dictionary, "a", "Osman");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }
    errorCode = addValue(dictionary, "b", "Commonwealth");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }
    errorCode = addValue(dictionary, "1", "Uther");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }
    errorCode = addValue(dictionary, "0", "Scorch");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }

    deleteValue(dictionary, "a");
    bool firstTest = !isContain(dictionary, "a");
    deleteValue(dictionary, "0");
    bool secondTest = !isContain(dictionary, "0");
    bool thirdTest = isContain(dictionary, "b");
    bool fourthTest = isContain(dictionary, "1");

    deleteTree(&dictionary);

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool isContainTest(void) {
    Dictionary *dictionary = createDictionary();
    int errorCode = addValue(dictionary, "a", "ParahodEntertainment");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }
    errorCode = addValue(dictionary, "b", "Jaina");
    if (errorCode) {
        deleteTree(&dictionary);
        return false;
    }

    bool firstTest = isContain(dictionary, "a");
    bool secondTest = isContain(dictionary, "b");
    bool thirdTest = !isContain(dictionary, "0");
    deleteValue(dictionary, "b");
    bool fourthTest = !isContain(dictionary, "b");

    deleteTree(&dictionary);

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool fullTest(void) {
    return createDictionaryTest() && deleteWordTest() && deleteTreeTest()
           && addWordTest() && isContainTest() && getWordTest();
}