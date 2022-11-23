#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct ListElement ListElement;

// create list, need to check for NULL
List* createList(void);

// add value to list by token, if token already exists change to new value
// if word already exists then increases frequency by one
// return 1 if not enough memory
// return 0 if all is ok
// return -1 if list doesn't exist
int addValue(List *list, unsigned int value);

// returns pointer to the first list element
ListElement* getFirstListElement(List *list);

// returns pointer to next list element, it may be NULL if it's the last one
ListElement* getNextElement(ListElement* element);

// returns value of list element by its pointer
// errorCode gets 1 if list element doesn't exist
// errorCode stay 0 if all is ok
unsigned int getListElementValue(ListElement* element, int *errorCode);

// deallocate list's memory
void deleteList(List **list);

// test all lists functions
// returns true if all tests passed
// returns false if tests didn't pass
bool listTest(void);