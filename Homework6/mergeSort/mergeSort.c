#include "mergeSort.h"
#include <string.h>

List* merge(List *firstOne, List *secondOne, Priority priority) {
    List *temp = createList();

    Position *firstPiece = createPosition();
    getFirstPosition(firstOne, firstPiece);
    Position *secondPiece = createPosition();
    getFirstPosition(secondOne, secondPiece);
    int errorCode = 0;

    // merge sort algorithm
    while (!isPositionNull(firstPiece) && !isPositionNull(secondPiece)) {
        char *first = getPositionValue(firstPiece, priority, &errorCode);
        char *second = getPositionValue(secondPiece, priority, &errorCode);
        if (strcmp(first, second) <= 0) {
            errorCode = insert(temp, firstPiece);
            if (errorCode) {
                deletePosition(&firstPiece);
                deletePosition(&secondPiece);
                deleteListMemory(&firstOne);
                deleteListMemory(&secondOne);
                return NULL;
            }
            getNextPosition(firstPiece);
        } else {
            errorCode = insert(temp, secondPiece);
            if (errorCode) {
                deletePosition(&firstPiece);
                deletePosition(&secondPiece);
                deleteListMemory(&firstOne);
                deleteListMemory(&secondOne);
                return NULL;
            }
            getNextPosition(secondPiece);
        }
    }

    // put extra elements to list
    while (!isPositionNull(firstPiece)) {
        errorCode = insert(temp, firstPiece);
        if (errorCode) {
            deletePosition(&firstPiece);
            deletePosition(&secondPiece);
            deleteListMemory(&firstOne);
            deleteListMemory(&secondOne);
            return NULL;
        }
        getNextPosition(firstPiece);
    }
    while (!isPositionNull(secondPiece)) {
        errorCode = insert(temp, secondPiece);
        if (errorCode) {
            deletePosition(&firstPiece);
            deletePosition(&secondPiece);
            deleteListMemory(&firstOne);
            deleteListMemory(&secondOne);
            return NULL;
        }
        getNextPosition(secondPiece);
    }

    // free list
    deletePosition(&firstPiece);
    deletePosition(&secondPiece);
    deleteListMemory(&firstOne);
    deleteListMemory(&secondOne);

    return temp;
}

List* sort(List* head, Priority priority) {
    // check for one element in list
    if (head == NULL) {
        return NULL;
    }
    Position *first = createPosition();
    getFirstPosition(head, first);
    if (isEnd(first)) {
        deletePosition(&first);
        return head;
    }
    deletePosition(&first);

    // create position on middle of list
    Position *middle = createPosition();
    getMiddlePosition(head, middle);
    List *secondHead = NULL;

    // check if list has only two elements
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

    // divide one list to two other
    cutList(middle);
    deletePosition(&middle);
    List* finalHead = NULL;
    // make recursion
    finalHead = merge(sort(head, priority), sort(secondHead, priority), priority);

    return finalHead;
}
