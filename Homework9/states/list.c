#include "list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct ListElement {
    struct ListElement* next;
    unsigned int value;
} ListElement;

typedef struct List {
    ListElement *head;
} List;

List* createList(void) {
    List *temp = malloc(sizeof(List));
    if (temp == NULL) {
        return NULL;
    }

    temp->head = NULL;

    return temp;
}

ListElement* createNode(unsigned int value) {
    ListElement *tempElement = malloc(sizeof(ListElement));
    if (tempElement == NULL) {
        return NULL;
    }

    tempElement->value = value;
    tempElement->next = NULL;

    return tempElement;
}

int addValue(List *list, unsigned int value) {
    if (list == NULL) {
        return -1;
    }

    ListElement *tempElement = createNode(value);
    if (tempElement == NULL) {
        return 1;
    }

    tempElement->next = list->head;
    list->head = tempElement;

    return 0;
}

ListElement* getFirstListElement(List *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

ListElement* getNextElement(ListElement* element) {
    if (element == NULL) {
        return NULL;
    }

    return element->next;
}

unsigned int getListElementValue(ListElement* element, int *errorCode) {
    if (element == NULL) {
        *errorCode = 1;
        return 0;
    }

    return element->value;
}

void printList(List *list) {
    if (list == NULL) {
        return;
    }

    ListElement *currentElement = list->head;
    while (currentElement != NULL) {
        printf("%u", currentElement->value);
        currentElement = currentElement->next;
    }
}

void deleteList(List **list) {
    if (list == NULL) {
        return;
    }

    ListElement *currentElement = (*list)->head;
    ListElement *previousElement = NULL;
    while (currentElement != NULL) {
        previousElement = currentElement;
        currentElement = currentElement->next;

        free(previousElement);
    }

    free(*list);
}