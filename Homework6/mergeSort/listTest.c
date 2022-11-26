#include "listTest.h"
#include <string.h>


bool createListTest(void) {
    List* list = createList();
    if (list == NULL) {
        return false;
    }

    bool result = list != NULL;
    deleteList(&list, false);

    return result;
}

bool deleteListMemoryTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    bool firstTest = list != NULL;
    deleteListMemory(&list);
    bool secondTest = list == NULL;

    return firstTest && secondTest;
}

bool createListByElementAndGetNextElementTest(void) {
    List *firstList = createList();
    int errorCode = 0;

    putHead(firstList, "checkFirst", "1");
    putHead(firstList, "checkSecond", "2");
    putHead(firstList, "checkThird", "3");

    ListElement *element = getFirstListElement(firstList);
    element = getNextListElement(element);
    List *testList = createListByElement(element);
    if (testList == NULL) {
        deleteList(&firstList, false);
        return false;
    }

    ListElement *secondElement = getFirstListElement(testList);
    bool testFirst = strcmp(getListElementValue(secondElement, name), "checkSecond");
    secondElement = getNextListElement(element);
    bool testSecond = strcmp(getListElementValue(secondElement, name), "checkFirst");

    deleteList(&firstList, false);
    deleteListMemory(&testList);

    return !testFirst && !testSecond;
}

bool getFirstPositionTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    int errorCode = 0;
    putHead(list, "CheckFirst", "1");
    putHead(list, "CheckSecond", "2");
    ListElement *element = getFirstListElement(list);
    bool correctTest = strcmp(getListElementValue(element, name), "CheckSecond");

    deleteList(&list, false);

    return !correctTest;
}

bool getFromFileTest(void) {
    char *fileName = "test.txt";
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    int errorCode = 0;

    getFromFile(fileName, list);
    ListElement *element = getFirstListElement(list);

    bool firstTest = !strcmp(getListElementValue(element, name), "bobbyKotik")
            && !strcmp(getListElementValue(element, phoneNumber), "999");

    element = getNextListElement(element);

    bool secondTest = !strcmp(getListElementValue(element, name), "uchkuduk")
            && !strcmp(getListElementValue(element, phoneNumber), "3");

    element = getNextListElement(element);

    bool thirdTest = !strcmp(getListElementValue(element, name), "qaraquyunlyu")
            && !strcmp(getListElementValue(element, phoneNumber), "880");

    deleteList(&list, true);

    return firstTest && secondTest && thirdTest;
}

bool isEndTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    putHead(list, "JustTest", "1024");
    ListElement *element = getFirstListElement(list);
    bool test = isEnd(element);

    deleteList(&list, false);

    return test;
}

bool deleteListTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    putHead(list, "Warian", "123");
    putHead(list, "Thrall", "12415");
    bool firstTest = list != NULL;
    deleteList(&list, false);
    bool secondTest = list == NULL;

    return firstTest && secondTest;
}

bool getMiddlePositionTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    int errorCode = 0;

    putHead(list, "Warian", "123");
    putHead(list, "Thrall", "12415");
    putHead(list, "Vol-jin", "123");

    ListElement *element = getMiddleListElement(list);
    bool test = strcmp(getListElementValue(element, name), "Thrall");

    deleteList(&list, false);

    return !test;
}

bool insertTest(void) {
    List *firstList = createList();
    if (firstList == NULL) {
        return false;
    }

    int errorCode = 0;
    putHead(firstList, "testFirst", "1");
    putHead(firstList, "testSecond", "2");

    List *secondList = createList();
    if (secondList == NULL) {
        deleteList(&firstList, false);
        return false;
    }

    ListElement *firstElement = getFirstListElement(firstList);
    ListElement *nextElement = getNextListElement(firstElement);
    insert(secondList, firstElement);
    insert(secondList, nextElement);

    firstElement = getFirstListElement(secondList);

    bool firstTest = strcmp(getListElementValue(firstElement, name), "testSecond");
    firstElement = getNextListElement(firstElement);
    bool secondTest = strcmp(getListElementValue(firstElement, name), "testFirst");

    deleteList(&firstList, false);
    deleteListMemory(&secondList);

    return !firstTest && !secondTest;
}

bool fullTest(void) {
    return createListTest() && deleteListTest() && deleteListMemoryTest()
    && getFromFileTest() && getFirstPositionTest() && getMiddlePositionTest()
    && insertTest() && isEndTest();
}
