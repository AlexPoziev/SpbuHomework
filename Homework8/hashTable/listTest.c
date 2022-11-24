#include "list.h"
#include "listTest.h"
#include <stdlib.h>
#include <string.h>

bool createListTest(void) {
    List *list = createList();

    bool test = list != NULL;

    deleteList(&list);

    return test;
}

bool addWordTest(void) {
    List *list = createList();

    int errorCode = 0;

    addWord(list, "check");
    addWord(list, "check");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "CommonWealth");

    ListElement *element = getFirstListElement(list);
    bool firstTest = !strcmp("check", getElementWord(element)) && getElementFrequency(element, &errorCode) == 2;
    element = getNextListElement(element);
    bool secondTest = !strcmp("test", getElementWord(element)) && getElementFrequency(element, &errorCode) == 3;
    element = getNextListElement(element);
    bool thirdTest = !strcmp("CommonWealth", getElementWord(element)) && getElementFrequency(element, &errorCode) == 1;

    deleteList(&list);

    return firstTest && secondTest && thirdTest;
}

bool getListLengthTest(void) {
    List *list = createList();

    bool firstTest = getListLength(list) == 0;
    addWord(list, "check");
    addWord(list, "check");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "test");

    bool secondTest = getListLength(list) == 2;

    addWord(list, "CommonWealth");
    addWord(list, "Burgundy");

    bool thirdTest = getListLength(list) == 4;

    deleteList(&list);

    return firstTest && secondTest && thirdTest;
}

bool deleteListTest(void) {
    List *list = createList();

    addWord(list, "test");

    deleteList(&list);

    return list == NULL;
}

bool getFirstTest(void) {
    List *list = createList();

    addWord(list, "check");
    addWord(list, "test");

    int errorCode = 0;
    List *test = getFirst(&list, &errorCode);
    if (errorCode == 1) {
        return false;
    }

    bool firstTest = !strcmp(getFirstWord(test), "check");
    bool secondTest = !strcmp(getFirstWord(list), "test");

    deleteList(&test);
    deleteList(&list);

    return firstTest && secondTest;
}

bool putListTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    List *testList = createList();
    if (testList == NULL) {
        free(list);
        return false;
    }

    addWord(list, "check");
    addWord(list, "test");

    putList(testList, &list);
    ListElement *element = getFirstListElement(testList);

    bool firstTest = list == NULL;
    bool secondTest = !strcmp(getElementWord(element), "check");
    element = getNextListElement(element);
    bool thirdTest = !strcmp(getElementWord(element), "test");

    deleteList(&testList);

    return firstTest && secondTest && thirdTest;
}

bool getFirstListElementTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    addWord(list, "check");
    addWord(list, "test");

    ListElement *element = getFirstListElement(list);
    bool test = !strcmp(getElementWord(element), "check");

    deleteList(&list);

    return test;
}

bool getNextListElementTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    addWord(list, "check");
    addWord(list, "test");

    ListElement *element = getFirstListElement(list);
    bool firstTest = !strcmp(getElementWord(element), "check");
    element = getNextListElement(element);
    bool secondTest = !strcmp(getElementWord(element), "test");

    deleteList(&list);

    return firstTest && secondTest;
}

bool getElementWordTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    addWord(list, "check");
    addWord(list, "test");

    ListElement *element = getFirstListElement(list);

    bool firstTest = !strcmp(getElementWord(element), "check");
    element = getNextListElement(element);
    bool secondTest = !strcmp(getElementWord(element), "test");

    deleteList(&list);

    return firstTest && secondTest;
}

bool getElementFrequencyTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    addWord(list, "check");
    addWord(list, "check");
    addWord(list, "check");
    addWord(list, "test");

    ListElement *element = getFirstListElement(list);
    int errorCode = 0;

    bool firstTest = getElementFrequency(element, &errorCode) == 3;
    element = getNextListElement(element);
    bool secondTest = getElementFrequency(element, &errorCode) == 1;
    element = getNextListElement(element);
    bool thirdTest = getElementFrequency(element, &errorCode) == 0;

    deleteList(&list);

    return firstTest && secondTest && thirdTest;
}



bool listTest(void) {
    return createListTest() && addWordTest() && getListLengthTest()
        && deleteListTest() && getFirstTest() && putListTest()
        && getElementWordTest() && getElementFrequencyTest()
        && getFirstListElementTest() && getNextListElementTest();
}