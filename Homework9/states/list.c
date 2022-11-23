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

ListElement* createListElement(unsigned int value) {
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

    ListElement *tempElement = createListElement(value);
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

void deleteList(List **list) {
    if (list == NULL || *list == NULL) {
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
    *list = NULL;
}

// tests

bool createListTest(void) {
    List *list = createList();

    bool test = list != NULL;

    deleteList(&list);

    return test;
}

bool addValueTest(void) {
    List *list = createList();

    addValue(list, 1);
    addValue(list, 2);
    addValue(list,3);

    bool firstTest = list->head->value == 3;
    bool secondTest = list->head->next->value == 2;
    bool thirdTest = list->head->next->next->value == 1;

    deleteList(&list);

    return firstTest && secondTest && thirdTest;
}


bool deleteListTest(void) {
    List *list = createList();

    addValue(list, 1);

    deleteList(&list);

    return list == NULL;
}

bool getFirstListElementTest(void) {
    List *list = createList();

    ListElement *element = getFirstListElement(list);

    bool firstTest = element == NULL;

    addValue(list, 1);
    addValue(list, 2);
    addValue(list,3);

    element = getFirstListElement(list);

    bool secondTest = element->value == 3;

    deleteList(&list);

    return firstTest && secondTest;
}

bool getNextElementTest(void) {
    List *list = createList();

    ListElement *element = getFirstListElement(list);
    bool firstTest = element == NULL;

    addValue(list, 1);
    addValue(list, 2);
    addValue(list,3);

    element = getFirstListElement(list);
    bool secondTest = element->value == 3;

    element = getNextElement(element);
    bool thirdTest = element->value == 2;

    element = getNextElement(element);
    bool fourthTest = element->value == 1;

    element = getNextElement(element);
    bool fifthTest = element == NULL;

    deleteList(&list);

    return firstTest && secondTest && thirdTest && fourthTest && fifthTest;
}

bool getNextElementValueTest(void) {
    List *list = createList();

    ListElement *element = getFirstListElement(list);
    bool firstTest = element == NULL;

    addValue(list, 1);
    addValue(list, 2);
    addValue(list,3);

    int errorCode = 0;

    element = getFirstListElement(list);
    bool secondTest = getListElementValue(element, &errorCode) == 3;

    element = getNextElement(element);
    bool thirdTest = getListElementValue(element, &errorCode) == 2;

    element = getNextElement(element);
    bool fourthTest = getListElementValue(element, &errorCode) == 1;


    deleteList(&list);

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool listTest(void) {
    return addValueTest() && getFirstListElementTest() && getNextElementTest()
        && deleteListTest() && createListTest() && getNextElementValueTest();
}