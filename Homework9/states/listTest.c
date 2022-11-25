#include "listTest.h"

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

bool addValueTest(void) {
    List *list = createList();

    int errorCode = 0;

    errorCode = addValue(list, 1);
    errorCode = addValue(list, 2);
    errorCode = addValue(list, 3);

    ListElement *element = getFirstListElement(list);
    bool firstTest = getListElementValue(element, &errorCode) == 3;
    element = getNextElement(element);
    bool secondTest = getListElementValue(element, &errorCode) == 2;
    element = getNextElement(element);
    bool thirdTest = getListElementValue(element, &errorCode) == 1;

    deleteList(&list);

    return firstTest && secondTest && thirdTest;
}


bool deleteListTest(void) {
    List *list = createList();

    addValue(list, 1);

    deleteList(&list);

    return list == NULL;
}

bool getFirstListElementTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    addValue(list, 1);
    addValue(list, 2);

    int errorCode = 0;
    ListElement *element = getFirstListElement(list);
    bool test = getListElementValue(element, &errorCode) == 2;

    deleteList(&list);

    return test;
}

bool getNextListElementTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    addValue(list, 1);
    addValue(list, 2);

    int errorCode = 0;

    ListElement *element = getFirstListElement(list);
    bool firstTest = getListElementValue(element, &errorCode) == 2;
    element = getNextElement(element);
    bool secondTest = getListElementValue(element, &errorCode) == 1;

    deleteList(&list);

    return firstTest && secondTest;
}

bool getListElementValueTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    addValue(list, 1);
    addValue(list, 2);

    ListElement *element = getFirstListElement(list);

    int errorCode = 0;

    bool firstTest = getListElementValue(element, &errorCode) == 2;
    element = getNextElement(element);
    bool secondTest = getListElementValue(element, &errorCode);

    deleteList(&list);

    return firstTest && secondTest;
}



bool listTest(void) {
    return createListTest() && addValueTest() && getFirstListElementTest()
        && getNextListElementTest() && getListElementValueTest() && deleteListTest();
}