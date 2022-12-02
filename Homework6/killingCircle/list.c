#include "list.h"

#include <stdio.h>

typedef struct ListElement {
    int value;
    int position;
    struct ListElement *previous;
    struct ListElement *next;
} ListElement;

typedef struct List {
    ListElement *head;
} List;

int isSingle(List* list) {
    return list->head == list->head->next;
}

ListElement* getFirstElement(List *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

List* createList(void) {
    List *temp = malloc(sizeof(List));
    temp->head = NULL;

    return temp;
}

ListElement* getNextListElement(ListElement *element) {
    if (element == NULL) {
        return NULL;
    }

    return element->next;
}

bool isEmptyNode(ListElement *node) {
    return node == NULL;
}

void plusOnePosition(ListElement *next, List *list) {
    ListElement *temp = next;
    while (temp != list->head->previous) {
        ++(temp->position);
        temp = temp->next;
    }

    ++(list->head->previous->position);
}

ListElement* findPosition(List *list, int position) {
    if (isEmpty(list) || isEmptyNode(list->head)) {
        return NULL;
    }

    ListElement *temp = list->head;

    while (temp->position != position) {
        if (temp->next == NULL) {
            return NULL;
        }

        temp = temp->next;
    }

    return temp;
}

int deleteListElement(List *list, ListElement **element) {
    (*element)->previous->next = (*element)->next;
    (*element)->next->previous = (*element)->previous;
    if ((*element) == list->head) {
        list->head = (*element)->next;
    }

    int temp = (*element)->value;

    ListElement *previousElement = *element;
    *element = getNextListElement(*element);
    free(previousElement);

    return temp;
}

int insert(List *list, int value, int position) {
    if (list == NULL) {
        return -1;
    }

    if (list->head == NULL) {
        ListElement *newNode = malloc(sizeof(ListElement));
        if (newNode == NULL) {
            return 1;
        }

        newNode->next = newNode;
        newNode->previous = newNode;
        newNode->value = value;
        newNode->position = position;
        list->head = newNode;

        return 0;
    }

    if (position < 0 || position > list->head->previous->position + 1) {
        return -1;
    }

    if (position == list->head->previous->position + 1) {
        ListElement *newNode = malloc(sizeof(ListElement));
        if (newNode == NULL) {
            return 1;
        }

        newNode->next = list->head;
        newNode->previous = list->head->previous;
        list->head->previous->next = newNode;
        list->head->previous = newNode;
        newNode->value = value;
        newNode->position = position;

        return 0;
    }

    ListElement *currentNode = findPosition(list, position);
    if (currentNode == NULL) {
        return -1;
    }

    ListElement *newNode = malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }

    newNode->value = value;
    newNode->position = position;
    currentNode->previous->next = newNode;
    currentNode->next->previous = newNode;
    newNode->previous = currentNode->previous;
    newNode->next = currentNode;
    if (position == 0) {
        list->head = newNode;
    }

    plusOnePosition(newNode->next, list);

    return 0;
}

bool isEmpty(List *list) {
    return list == NULL;
}

void clear(List **list) {
    ListElement *next = (*list)->head;
    while (next != (*list)->head) {
        (*list)->head = (*list)->head->next;
        free(next);
        next = (*list)->head;
    }

    free(*list);
    (*list) = NULL;
}

