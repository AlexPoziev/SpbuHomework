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

    return firstTest == 2 && secondTest == 0 && thirdTest == 1 && fourthTest == -1 && fifthTest == -1;
}

bool isSingleTest(void) {
    List *list = createList();
    insert(list, 0, 0);
    bool firstTest = isSingle(list);
    insert(list, 1, 0);
    bool secondTest = isSingle(list);

    return firstTest && !secondTest;
}

bool PositionTest(void) {
    int errorCode = 0;
    List *list = createList();
    insert(list, 0, 0);
    insert(list, 1, 0);
    bool secondTest = isSingle(list);

    Position *position = createPosition(list);
    Position *firstTest = position;
    getNextPosition(firstTest);
    int thirdTest = deletePosition(list, position, &errorCode);
    bool fourthTest = isSingle(list);

    
    return firstTest == position && !secondTest && fourthTest && thirdTest == 1;
}

