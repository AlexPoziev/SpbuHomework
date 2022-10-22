#include <stdio.h>
#include "testList.h"
#include "list.h"

int circleOfDeath(int numbersCount, int gap, int *errorCode) {
    if (numbersCount <= 0 || gap <= 0) {
        return -1;
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
    clear(&list, position);

    return temp;
}

int main() {
    if (!isSingleTest()) {
        printf("Tests Failed");
        return 1;
    }
    return 0;
}
