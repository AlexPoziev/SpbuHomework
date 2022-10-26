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

    return temp;
}

List* sort(List* head) {
    Priority priority = name;

    Position *first = createPosition();
    getFirstPosition(head, first);
    getNextPosition(first);
    if (isPositionNull(first)) {
        return head;
    }

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
        secondHead = createPositionList(middle);
    }
    cutList(middle);

    List* finalHead = createList();
    finalHead = merge(sort(head), sort(secondHead), priority);

    return finalHead;
}
