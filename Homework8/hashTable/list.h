#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct ListElement ListElement;

// create list, need to check for NULL
List* createList(void);

// add word to list by token, if token already exists change to new value
// if word already exists then increases frequency by one
// return 1 if not enough memory
// return 0 if all is ok
int addWord(List *list, char* word);

// print full list.
// returns count of successfully printed elements
int printList(List *list);

// deallocate list's memory
void deleteList(List **list);

// test all lists functions
// returns true if all tests passed
// returns false if tests didn't pass
bool listTest(void);

// returns length of list
unsigned int getListLength(List *list);

// return list with one element, which is the first element in incoming list and delete it from list
// free and NULL List pointer if you get last element from it
// return NULL if list is empty
// errorCode is 1 if not enough memory
List* getFirst(List **list, int *errorCode);

// add sourceList into destinationList and delete sourceList
// doesn't check for equal list elements
void putList(List *destinationList, List **sourceList);

// returns word of first list element
// return NULL if no first element or list doesn't exist
char* getFirstWord(List* list);

// return string of list element
char* getElementWord(ListElement *element);

// return frequency value of list element
// errorCode gets -1 value if NULL element
unsigned int getElementFrequency(ListElement *element, int *errorCode);

// return pointer to first list element of list
ListElement* getFirstListElement(List* list);

// return pointer to next list element
ListElement* getNextListElement(ListElement *element);