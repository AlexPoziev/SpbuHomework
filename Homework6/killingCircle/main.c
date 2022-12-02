#include <stdio.h>

#include "testList.h"
#include "list.h"

int circleOfDeath(int numbersCount, int gap, int *errorCode) {
    if (numbersCount <= 0 || gap <= 0) {
        *errorCode = -1;
        return -1;
    }

    if (gap == 1) {
        return numbersCount;
    }

    List *list = createList();
    if (list == NULL) {
        *errorCode = 1;
        return 1;
    }

    for (int i = 0; i < numbersCount; ++i) {
        *errorCode = insert(list, i + 1, i);
        if (*errorCode != 0) {
            return *errorCode;
        }
    }

    ListElement *element = getFirstElement(list);
    int step = 1;
    while (!isSingle(list)) {
        ++step;
        element = getNextListElement(element);
        if (step == gap) {
            deleteListElement(list, &element);
            if (*errorCode) {
                return *errorCode;
            }

            step = 1;
        }
    }

    int temp = deleteListElement(list, &element);

    clear(&list);

    return temp;
}

bool correctTests(void) {
    int errorCode = 0;
    int firstTest = circleOfDeath(17, 2, &errorCode);
    int secondTest = circleOfDeath(1, 15, &errorCode);
    int thirdTest = circleOfDeath(15, 1, &errorCode);
    int errorCodeCheck = 0;
    circleOfDeath(-1, -5, &errorCodeCheck);

    return firstTest == 3 && secondTest == 1 && thirdTest == 15 && !errorCode && errorCodeCheck;
}

int main() {
    if (!fullTest() || !correctTests()) {
        printf("Tests Failed");
        return 1;
    }

    int errorCode = 0;
    printf("Input count of Suicide Squad, greater than zero: ");
    int numbers = 0;
    scanf("%d", &numbers);
    printf("Input gap, greater than zero: ");
    int gap = 0;
    scanf("%d", &gap);

    int lastStand = circleOfDeath(numbers, gap, &errorCode);
    if (errorCode == -1) {
        printf("Incorrect entered data");
        return -1;
    }
    if (errorCode == 1) {
        printf("Not enough memory");
        return 1;
    }

    printf("Last survivor: %d", lastStand);

    return 0;
}
