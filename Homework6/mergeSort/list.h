#pragma once

#include <stdbool.h>
#include <stdio.h>

// pointer to list element
typedef struct ListElement ListElement;

typedef struct List List;

// what functions need to put out
typedef enum Priority {
    name,
    phoneNumber
} Priority;

// create list, need to check not NULL pointer \/
List* createList(void);

// create list with started position \/
List* createListByElement(ListElement *element);

// get data from file and put it into the list
// return 1 if not enough memory
// return -1 if no corresponding phone number or name
// return -2 if file with fileName value doesn't exist\/
int getFromFile(char* fileName, List* list);

// print list \/
void printList (List *list);

// change input pointer to the first position of list \/
ListElement* getFirstPosition(List *list);

// get position of next list element. If next doesn't exist, return NULL \/
ListElement* getNextListElement(ListElement *element);

// get middle element of list \/
ListElement* getMiddleListElement(List *list);

// get value of list element \/
char* getListElementValue(ListElement *element, Priority priority);

// cut list by position \/
void cutList(ListElement *element);

// put to head
void putHead(List *list, char *name, char *phoneNumber);

// check is element end of list \/
bool isEnd(ListElement *element);

// insert value by list element to end of list. Return -1 if list doesn't exist \/
int insert(List *list, ListElement *element);

// clear memory list struct
void deleteListMemory(List **list);

// delete List, second parameter if got 1 - free memory for pointers of contacts, else doesn't \/
void deleteList(List **list, bool isAllocated);

// check is element NULL
bool isListElementNull(ListElement* element);