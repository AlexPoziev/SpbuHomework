#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

// add an element to the list, position not greater than list size
int insert(List *list, int value, int position);

// print full list
void print(List *list);

// delete element with index position below size of list
// Count starts by 0. Return deleted value. errorCode -1 means that position incorrect
int delete(List *list, int position, int *errorCode);

// change value of list in position. Returns errorCode, -1 means that position incorrect
int changeNode(List *list, int position, int value);

// checks is list empty
bool isEmpty(List *list);

// delete list and clear memory
int clear(List *list);

// find value by position in list, errorCode == -1 if position below zero or more than real size of list
int findNode(List *list, int position, int *errorCode);

// create list, need to check for not NULL
List* createList(void);

// delete element in cycle list, position may be greater than size of list
List* cycleListDelete(List *list, int position);

// insert element in cycle list, position may be greater than size of list
List* cycleListInsert(List *list, int position);

// return length of list
int listSize(List *list);