#include "mergeSort.h"
#include <string.h>

List* merge(List *firstOne, List *secondOne, Priority priority) {
    List *temp = createList();

    Position *firstPiece = createPosition();
    getFirstPosition(firstOne, firstPiece);
    Position *secondPiece = createPosition();
    getFirstPosition(secondOne, secondPiece);

    while (!isPositionNull(firstPiece) && !isPositionNull(secondPiece)) {
        int errorCode = 0;
        char *first = getPositionValue(firstPiece, priority, &errorCode);
        char *second = getPositionValue(secondPiece, priority, &errorCode);
        if (strcmp(first, second) <= 0) {
            insert(temp, firstPiece);
            getNextPosition(firstPiece);
        } else {
            insert(temp, secondPiece);
            getNextPosition(secondPiece);
        }
    }

    while (!isPositionNull(firstPiece)) {
        insert(temp, firstPiece);
        getNextPosition(firstPiece);
    }
    while (!isPositionNull(secondPiece)) {
        insert(temp, secondPiece);
        getNextPosition(secondPiece);
    }

    deletePosition(&firstPiece);
    deletePosition(&secondPiece);
    deleteListMemory(&firstOne);
    deleteListMemory(&secondOne);

    return temp;
}

List* sort(List* head, Priority priority) {
    Position *first = createPosition();
    getFirstPosition(head, first);
    if (isEnd(first)) {
        return head;
    }
    deletePosition(&first);

    Position *middle = createPosition();
    getMiddlePosition(head, middle);
    List *secondHead = NULL;
    if (isEnd(middle)) {
        secondHead = createPositionList(middle);
        getFirstPosition(head, middle);
    } else {
        Position *nextMiddle = createPosition();
        getMiddlePosition(head, nextMiddle);
        getNextPosition(nextMiddle);
        secondHead = createPositionList(nextMiddle);
        deletePosition(&nextMiddle);
    }
    cutList(middle);
    deletePosition(&middle);
    List* finalHead = NULL;
    finalHead = merge(sort(head, priority), sort(secondHead, priority), priority);

    return finalHead;
}
