#include "listTest.h"
#include <string.h>

bool fullTest(void) {

}

bool createListTest(void) {
    List* list = createList();
    bool result = list != NULL;
    deleteList(&list, false);

    return result;
}

bool createPositionTest(void) {
    Position* position = createPosition();
    bool result = position != NULL;
    deletePosition(&position);

    return result;
}

bool deletePositionTest(void) {
    List* list = createList();
    putHead(list, "test", "1");
    Position* position = NULL;
    getFirstPosition(list, position);
    bool resultFirst = position != NULL;
    deletePosition(&position);
    bool resultSecond = position == NULL;
    deleteList(&list, false);

    return resultFirst && resultSecond;
}

bool deleteListMemoryTest(void) {
    List *list = createList();
    bool firstTest = list != NULL;
    deleteListMemory(&list);
    bool secondTest = list == NULL;

    return firstTest && secondTest;
}

bool createPositionListTest(void) {
    List *firstList = createList();
    int errorCode = 0;

    putHead(firstList, "checkFirst", "1");
    putHead(firstList, "checkSecond", "2");
    putHead(firstList, "checkThird", "3");

    Position *position = createPosition();
    getFirstPosition(firstList, position);
    getNextPosition(position);
    List *testList = createPositionList(position);
    Position *testPosition = createPosition();
    getFirstPosition(testList, testPosition);
    char *firstCheck = getPositionValue(position, name, &errorCode);
    bool testFirst = strcmp(firstCheck, "checkSecond");
    getNextPosition(position);
    char *secondCheck = getPositionValue(position, name, &errorCode);
    bool testSecond = strcmp(secondCheck, "checkFirst");

    deletePosition(&position);
    deletePosition(&testPosition);
    deleteList(&firstList, false);
    deleteListMemory(&testList);

    return !testFirst && !testSecond;
}

bool getFirstPositionTest(void) {
    List *list = createList();
    int errorCode = 0;
    putHead(list, "CheckFirst", "1");
    putHead(list, "CheckSecond", "2");
    Position *position = createPosition();
    getFirstPosition(list, position);
    char *test = getPositionValue(position, name, &errorCode);
    bool correctTest = strcmp(test, "CheckSecond");

    deletePosition(&position);
    deleteList(&list, false);

    return !correctTest;
}

bool getNextPositionTest(void) {
    List *list = createList();
    int errorCode = 0;
    putHead(list, "CheckFirst", "1");
    putHead(list, "CheckSecond", "2");
    Position *position = createPosition();
    getFirstPosition(list, position);
    getNextPosition(position);
    char *test = getPositionValue(position, name, &errorCode);
    bool correctTest = strcmp(test, "CheckFirst");

    deletePosition(&position);
    deleteList(&list, false);

    return !correctTest;
}

bool getFromFileTest(void) {
    char *fileName = "test.txt";
    List *list = createList();
    FILE* file = NULL;
    int errorCode = 0;

    getFromFile(file, fileName, list);
    Position *position = createPosition();
    getFirstPosition(list, position);

    bool firstTest = strcmp(getPositionValue(position, name, &errorCode), "bobbyKotik")
            || strcmp(getPositionValue(position, phoneNumber, &errorCode), "999");
    getNextPosition(position);

    bool secondTest = strcmp(getPositionValue(position, name, &errorCode), "uchkuduk")
                     || strcmp(getPositionValue(position, phoneNumber, &errorCode), "3");
    getNextPosition(position);

    bool thirdTest = strcmp(getPositionValue(position, name, &errorCode), "qaraquyunlyu")
                      || strcmp(getPositionValue(position, phoneNumber, &errorCode), "880");
    getNextPosition(position);

    deletePosition(&position);
    deleteList(&list, true);

    return !firstTest && !secondTest && !thirdTest;
}

bool isEndTest(void) {
    List *list = createList();
    putHead(list, "JustTest", "1024");
    Position *position = createPosition();
    getFirstPosition(list, position);
    bool test = isEnd(position);

    deleteList(&list, false);
    deletePosition(&position);

    return test;
}

bool cutListTest(void) {
    List *list = createList();
    Position *position = createPosition();
    putHead(list, "JustTest", "1024");
    putHead(list, "JustTestt", "10234");
    putHead(list, "JustTesttt", "10244");

    getFirstPosition(list, position);
    getNextPosition(position);

    cutList(position);
    bool test = isEnd(position);

    deleteList(&list, false);
    deletePosition(&position);

    return test;
}

