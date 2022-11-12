#pragma once

#include <stdbool.h>

typedef struct List List;

// create list, need to check for NULL
List* createList(void);

// add word to list by token, if token already exists change to new value
// if word already exists then increases frequency by one
int addWord(List *list, char* word);

// print full list.
// returns count of successfully printed elements
int printList(List *list);

// deallocate list's memory
void deleteList(List **list);

// test all lists functions
bool listTest(void);