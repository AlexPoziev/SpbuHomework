#pragma once

#include <stdbool.h>

typedef struct Dictionary Dictionary;

// create dictionary, need to check for NULL
Dictionary* createDictionary(void);

// add value to dictionary by token, if token already exists change to new value
// return 0 if all OK
// return -1 if dictionary pointer NULL
// return 1 if not enough memory
int addValue(Dictionary *dictionary, int token, char* value);

// get value by token, if no token in dictionary, returns NULL
char* getValue(Dictionary *dictionary, int token);

// check containing token in dictionary
bool isContain(Dictionary *dictionary, int token);

// delete element of dictionary by token, if no token doing nothing
// return 0 if all OK
// return -1 if dictionary pointer NULL
// return 1 if not enough memory
int deleteWord(Dictionary *dictionary, int token);

// deallocate dictionary's memory
void deleteTree(Dictionary **dictionary);

// test work of algorithm and save of a balance in AVL tree
bool AVLTreeBalanceTest(void);