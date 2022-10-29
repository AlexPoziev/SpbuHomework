#pragma once
#include <stdbool.h>

typedef struct Dictionary Dictionary;

// create dictionary, need to check for NULL
Dictionary* createDictionary(void);

// add word to dictionary by token, if token already exists change to new value
int addWord(Dictionary *dictionary, int token, char* word);

// get word by token
char* getWord(Dictionary *dictionary, int token);

// check containing token in dictionary
bool isContain(Dictionary *dictionary, int token);

// delete element of dictionary by token, if no token doing nothing
int deleteWord(Dictionary *dictionary, int token);

// deallocate dictionary's memory
void deleteTree(Dictionary **dictionary);