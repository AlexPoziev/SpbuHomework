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
        if (*errorCode) {
            return *errorCode;
        }
    }
    Position *position = createPosition(list);
    if (position == NULL) {
        *errorCode = 1;
        return 1;
    }
    int step = 1;
    while(!isSingle(list)) {
        ++step;
        getNextPosition(position);
        if (step == gap) {
            deletePosition(list, position, errorCode);
            if (*errorCode) {
                return *errorCode;
            }
            step = 1;
        }
    }

    int temp = deletePosition(list, position, errorCode);

    clear(&list);
    deletePositionMemory(&position);

    return temp;
}

bool correctTests(void) {
    int errorCode = 0;
    int firstTest = circleOfDeath(17, 2, &errorCode);
    if ()
}

int main() {
    if (!fullTest()) {
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
