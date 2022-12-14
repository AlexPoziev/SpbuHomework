#pragma once

#include <stdbool.h>

typedef struct HashTable HashTable;

// create Hash table, need to check for NULL
HashTable* createHashTable(void);

// fills in the table words (separated by spaces). Gets file's name and pointer to hash table
// return -1 if no file with this name
// return 0 if all is ok
// return 1 if not enough memory
int getFromFile(char *fileName, HashTable *table);

// returns coefficient of occupancy in the hash table
double getHashTableOccupancy(HashTable *table);

// print all values of hash table
void printHashTable(HashTable *table);

// get max length of all lists in hashTable to maxLength pointer
// get average length of all lists in hashTable to averageLength pointer
// returns -1 if table == NULL
// returns 0 if all is ok
int getHashTablesListsInfo(HashTable *table, unsigned int *maxLength, double *averageLength);

// delete hashTable and clear memory
void deleteHashTable(HashTable **table);

// get frequency from hashTable by word
unsigned int getFrequencyByWord(HashTable *table, char *word, int *errorCode);

// return hashTable size
unsigned int getHashTableSize(HashTable *table);

// add value to hashTable
// return 1 if not enough memory
// return 0 if all is ok
int addValueToHashTable(HashTable *table, char *value);