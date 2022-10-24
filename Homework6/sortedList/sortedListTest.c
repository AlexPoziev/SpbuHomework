#include "sortedListTest.h"
#include "sortedList.h"
#include <stdlib.h>

bool getValueAndInsertTest(void) {
    List *list = createList();
    int errorCode = 0;

    insert(list, 10);
    insert(list, -1);

    int firstTest = getValue(list, &errorCode);
    delete(list, -1);
    int secondTest = getValue(list, &errorCode);

    deleteList(&list);

    return firstTest == -1 && secondTest == 10;
}

bool deleteTest(void) {
    List *list = createList();
    int errorCode = 0;
    int errorCodeNull = 0;
    insert(list, 10);
    insert(list, -1);

    int errorCodeTest = delete(list, 9);
    int errorCodeFirst = delete(list, 10);
    int testFirst = getValue(list, &errorCode);
    int errorCodeSecond = delete(list, -1);
    int testSecond = getValue(list, &errorCodeNull);

    bool fullCheck = errorCodeTest == -1 && testFirst == -1 && !errorCode && !errorCodeFirst
    && !errorCodeSecond && errorCodeNull;

    deleteList(&list);

    return fullCheck;
}

bool testSort(void) {
    List *list = createList();
    int errorCode = 0;
    insert(list, -1);
    insert(list, 10);
    insert(list, 0);

    int firstTest = getValue(list, &errorCode);
    delete(list, firstTest);
    int secondTest = getValue(list, &errorCode);
    delete(list,secondTest);
    int thirdTest = getValue(list, &errorCode);

    deleteList(&list);

    return firstTest == -1 && secondTest == 0 && thirdTest == 10;
}

bool createListTest(void) {
    List *list = createList();

    return list != NULL;
}

bool deleteListTest(void) {
    List *list = createList();

    insert(list, 10);
    insert(list, -1);

    deleteList(&list);

    return list == NULL;
}

bool fullTest(void) {
    return getValueAndInsertTest() && deleteListTest() && createListTest()
    && testSort() && deleteTest();
}