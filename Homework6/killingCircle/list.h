#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;
typedef struct Position Position;

// add an element to the list, position not greater than list size
int insert(List *list, int value, int position);

// return does list has only one element
int isSingle(List *list);

// create Position of list to first element, create only once
Position* createPosition(List *list);

// change position to next position, but clear previous position pointer. return -1 if NULL Position pointer
int getNextPosition(Position *position);

// delete element of list by position pointer;
// Count starts by 0. Return deleted value. errorCode -1 means that position incorrect
int deletePosition(List *list, Position *position, int *errorCode);

// clear list and position
void clear(List **list);

// checks is list empty
bool isEmpty(List *list);

// create list, need to check for not NULL
List* createList(void);

// free memory of position
void deletePositionMemory(Position** position);

