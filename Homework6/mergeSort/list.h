#pragma once

#include <stdbool.h>
#include <stdio.h>

// pointer to list element
typedef struct Position Position;

typedef struct List List;

// what functions need to put out
typedef enum Priority {
    name,
    phoneNumber
} Priority;

// create list, need to check not NULL pointer \/
List* createList(void);

// create Position, need to check ton NULL pointer \/
Position* createPosition(void);

// get data from file and put it into the list
void getFromFile(FILE* file, char* fileName, List* list);

// print list \/
void printList (List *list);

// change input pointer to the first position of list \/
void getFirstPosition(List *list, Position *position);

// get position of next list element. If next doesn't exist, return NULL \/
void getNextPosition(Position *position);

// get position of middle element of list \/
void getMiddlePosition(List *list, Position *position);

// get value by Position \/
char* getPositionValue(List *list, Position *position, Priority priority, int *errorCode);

// add new element after current position with new position number \/
void addNext(Position *currentPosition, Position *newPosition);

// check is Position end of list \/
bool isEnd(Position *position);

// insert value by position pointer to end of list. Return -1 if list doesn't exist \/
int insert(List *list, Position *position);

// delete Position \/
void deletePosition(Position **position);

// delete List \/
void deleteList(List **list);