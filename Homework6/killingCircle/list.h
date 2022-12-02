#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

typedef struct ListElement ListElement;

// add an element to the list, position not greater than list size
int insert(List *list, int value, int position);

// return does list has only one element
int isSingle(List *list);

// delete list element from cycle list
int deleteListElement(List *list, ListElement **element);

// return pointer to first element
ListElement* getFirstElement(List *list);

// return next listElement
ListElement* getNextListElement(ListElement *position);

// clear list
void clear(List **list);

// checks is list empty
bool isEmpty(List *list);

// create list, need to check for not NULL
List* createList(void);

