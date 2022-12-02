#include "testList.h"

bool insertAndDeleteAndGetFirstTest(void) {
    int errorCode = 0;
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    insert(list, 0, 0);
    insert(list, 1, 1);
    insert(list, 2, 0);
    int fourthTest = insert(list, 10, 10);
    int fifthTest = insert(list, 10, -1);

    ListElement *element = getFirstElement(list);
    int firstTest = deleteListElement(list, &element);
    int secondTest = deleteListElement(list, &element);
    int thirdTest = deleteListElement(list, &element);

    clear(&list);

    return firstTest == 2 && secondTest == 0 && thirdTest == 1 && fourthTest == -1 && fifthTest == -1;
}

bool isSingleTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    insert(list, 0, 0);
    bool firstTest = isSingle(list);
    insert(list, 1, 0);
    bool secondTest = isSingle(list);

    clear(&list);

    return firstTest && !secondTest;
}

bool clearTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    insert(list, 1, 1);
    insert(list, 2, 2);

    bool firstTest = getFirstElement(list) != NULL;

    clear(&list);

    return firstTest && list == NULL;
}

bool getNextListElementTest(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }

    insert(list, 10, 1);
    insert(list, 20, 2);

    ListElement *element = getFirstElement(list);
    element = getNextListElement(element);
    bool firstTest = element != getFirstElement(list);
    element = getNextListElement(element);
    bool secondTest = element == getFirstElement(list);

    clear(&list);

    return firstTest && secondTest;
}

bool fullTest(void) {
    return insertAndDeleteAndGetFirstTest() && isSingleTest()
        && clearTest() && getNextListElementTest();
}

