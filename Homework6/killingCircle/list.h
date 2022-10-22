#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;
typedef struct Position Position;

// add an element to the list, position not greater than list size
int insert(List *list, int value, int position);

// return size of list
int listSize(List *list);

// print full list
int print(List *list);

// create Position of list element, create only once
Position* createPosition(void);

// change position to next position, but clear previous position pointer. return -1 if NULL Position pointer
int getNextPosition(Position *position);

// delete element of list by position pointer;
// Count starts by 0. Return deleted value. errorCode -1 means that position incorrect
int deletePosition(List *list, int position, int *errorCode);

// change value of list in position. Returns errorCode, -1 means that position incorrect
int changeNode(List *list, int position, int value);

// checks is list empty
bool isEmpty(List *list);

// delete list and clear memory
void deleteList(List **list);

// find value by position in list, errorCode == -1 if position below zero or more than real size of list
int findNode(List *list, int position, int *errorCode);

// create list, need to check for not NULL
List* createList(void);
