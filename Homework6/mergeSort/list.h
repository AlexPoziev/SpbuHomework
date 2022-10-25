#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct Position Position;

typedef struct List List;

// create list, need to check not NULL pointer
List* createList(void);

// create Position, need to check ton NULL pointer
Position* createPosition(void);

// get data from file and put it into the list
void getFromFile(FILE* file, char* fileName, List* list);

// print list
void printList (List *list);

// get position of next list element. If next doesn't exist, return NULL
Position* getNextPosition(List *list, Position *position);

// get value by Position
char* getPositionValue(List *list, Position *position);

// check is Position end of list
bool isEnd(List *list, Position *position);

// insert value to end of list. Return 1 if not enough memory
int insert(List *list, char *value);

// change value of position
int changePositionValue(List *list, Position *position, char *value);

// get position of middle element of list
Position* getMiddlePosition(List *list);