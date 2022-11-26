#include "mergeSortTest.h"
#include "list.h"

#include <string.h>

bool mergeSortTest(void) {
    int errorCode = 0;
    List *firstTest = createList();
    if (firstTest == NULL) {
        return false;
    }

    putHead(firstTest, "abcde", "12345");
    putHead(firstTest, "baaaa", "11");
    putHead(firstTest, "abcdf", "12344");
    putHead(firstTest, "y", "99990");

    firstTest = sort(firstTest, name, &errorCode);
    if (errorCode == 1) {
        deleteList(&firstTest, false);
        return false;
    }

    ListElement *element = getFirstListElement(firstTest);
    bool nameTestFirst = strcmp(getListElementValue(element, name), "abcde");
    element = getNextListElement(element);
    bool nameTestSecond = strcmp(getListElementValue(element, name), "abcdf");
    element = getNextListElement(element);
    bool nameTestThird = strcmp(getListElementValue(element, name), "baaaa");
    element = getNextListElement(element);
    bool nameTestFourth = strcmp(getListElementValue(element, name), "y");

    firstTest = sort(firstTest, phoneNumber, &errorCode);
    if (errorCode == 1) {
        deleteList(&firstTest, false);
        return false;
    }

    element = getFirstListElement(firstTest);
    bool phoneNumberTestFirst = strcmp(getListElementValue(element, phoneNumber), "11");
    element = getNextListElement(element);
    bool phoneNumberTestSecond = strcmp(getListElementValue(element, phoneNumber), "12344");
    element = getNextListElement(element);
    bool phoneNumberTestThird = strcmp(getListElementValue(element, phoneNumber), "12345");
    element = getNextListElement(element);
    bool phoneNumberTestFourth = strcmp(getListElementValue(element, phoneNumber), "99990");

    deleteList(&firstTest, false);

    return !nameTestFirst && !nameTestSecond && !nameTestThird && !nameTestFourth
    && !phoneNumberTestFirst && !phoneNumberTestSecond && !phoneNumberTestThird && !phoneNumberTestFourth;
}