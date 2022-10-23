#include "testList.h"

bool insertTest(void) {
    int errorCode = 0;
    List *list = createList();
    insert(list, 0, 0);
    insert(list, 1, 1);
    insert(list, 2, 0);
    int fourthTest = insert(list, 10, 10);
    int fifthTest = insert(list, 10, -1);

    Position *position = createPosition(list);
    int firstTest = deletePosition(list, position, &errorCode);
    int secondTest = deletePosition(list, position, &errorCode);
    int thirdTest = deletePosition(list, position, &errorCode);

    clear(&list);
    deletePositionMemory(&position);

    return firstTest == 2 && secondTest == 0 && thirdTest == 1 && fourthTest == -1 && fifthTest == -1;
}

bool isSingleTest(void) {
    List *list = createList();
    insert(list, 0, 0);
    bool firstTest = isSingle(list);
    insert(list, 1, 0);
    bool secondTest = isSingle(list);
    Position *position = createPosition(list);

    clear(&list);
    deletePositionMemory(&position);

    return firstTest && !secondTest;
}

bool positionTest(void) {
    int errorCode = 0;
    List *list = createList();
    insert(list, 0, 0);
    insert(list, 1, 0);
    bool secondTest = isSingle(list);

    Position *position = createPosition(list);
    Position *firstTest = position;
    getNextPosition(firstTest);
    int thirdTest = deletePosition(list, position, &errorCode);

    bool test = firstTest == position && !secondTest && thirdTest == 0;

    clear(&list);
    deletePositionMemory(&position);

    return test;
}

bool fullTest(void) {
    return insertTest() && isSingleTest() && positionTest();
}

