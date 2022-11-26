#include "mergeSort.h"
#include <string.h>
#include <stdlib.h>

List* merge(List *firstOne, List *secondOne, Priority priority, int *errorCode) {
    List *temp = createList();

    ListElement *firstPiece = getFirstListElement(firstOne);
    ListElement *secondPiece = getFirstListElement(secondOne);

    // merge sort algorithm
    while (!isListElementNull(firstPiece) && !isListElementNull(secondPiece)) {
        char *first = getListElementValue(firstPiece, priority);
        char *second = getListElementValue(secondPiece, priority);
        if (strcmp(first, second) <= 0) {
            ListElement *nextElement = getNextListElement(firstPiece);
            *errorCode = insert(temp, firstPiece);
            if (*errorCode) {
                deleteListMemory(&firstOne);
                deleteListMemory(&secondOne);
                return temp;
            }

            firstPiece = nextElement;
        } else {
            ListElement *nextElement = getNextListElement(secondPiece);
            *errorCode = insert(temp, secondPiece);
            if (*errorCode) {
                deleteListMemory(&firstOne);
                deleteListMemory(&secondOne);
                return temp;
            }

            secondPiece = nextElement;
        }
    }
    // put extra elements to list
    while (!isListElementNull(firstPiece)) {
        ListElement *nextElement = getNextListElement(firstPiece);
        *errorCode = insert(temp, firstPiece);
        if (*errorCode) {
            deleteListMemory(&firstOne);
            deleteListMemory(&secondOne);
            return temp;
        }

        firstPiece = nextElement;
    }

    while (!isListElementNull(secondPiece)) {
        ListElement *nextElement = getNextListElement(secondPiece);
        *errorCode = insert(temp, secondPiece);
        if (*errorCode) {
            deleteListMemory(&firstOne);
            deleteListMemory(&secondOne);
            return temp;
        }

        secondPiece = nextElement;
    }

    // free list
    deleteListMemory(&firstOne);
    deleteListMemory(&secondOne);

    return temp;
}

List* sort(List* head, Priority priority, int *errorCode) {
    // check for one element in list
    if (head == NULL) {
        return NULL;
    }

    if (isEnd(getFirstListElement(head))) {
        return head;
    }

    // create position on middle of list
    ListElement *middle = getMiddleListElement(head);
    List *secondHead = NULL;

    // check if list has only two elements
    if (isEnd(middle)) {
        secondHead = createListByElement(middle);
        middle = getFirstListElement(head);
    } else {
        ListElement *nextMiddle = getMiddleListElement(head);
        nextMiddle = getNextListElement(nextMiddle);
        secondHead = createListByElement(nextMiddle);
    }

    // divide one list to two other
    cutList(middle);
    List* finalHead = NULL;
    // make recursion
    finalHead = merge(sort(head, priority, errorCode), sort(secondHead, priority, errorCode), priority, errorCode);
    if (*errorCode) {
        deleteList(&head, true);
        deleteList(&finalHead, true);
        deleteList(&secondHead, true);
    }

    return finalHead;
}