#pragma once
#include <stdbool.h>

typedef struct Dictionary Dictionary;

// create dictionary, need to check for NULL
Dictionary* createDictionary(void);

// add word to dictionary by token, if token already exists change to new value
int addWord(Dictionary *dictionary, int token, char* word);