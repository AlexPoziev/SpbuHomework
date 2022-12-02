#pragma once

typedef struct List List;

// create list, return pointer to allocated memory for list
List* createList(void);

// insert value to sorted list and save sorting. Returns 1 if get problems with memory
int insert(List *list, int value);

// delete list element by value. Returns -1 if no equal value in list
int delete(List *list, int value);

// print list
int printList(List *list);

// delete list
void deleteList(List **list);

// get value from head
int getValue(List *list, int *errorCode);