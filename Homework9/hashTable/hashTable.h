#pragma once

typedef struct HashTable HashTable;

// create Hash table, get hash table size, need to check for NULL
HashTable createHashTable(unsigned int tableSize);

// fills in the table words (separated by spaces). Gets file's name and pointer to hash table
// returns -1 if no file with this name
// return 0 if all is ok
int getFromFile(char *fileName, HashTable *table);

// returns coefficient of occupancy in the hash table
int getHashTableOccupancy(HashTable *table);

// get max length of all lists in hashTable to maxLength pointer
// get average length of all lists in hashTable to averageLength pointer
// returns -1 if table == NULL
// returns 1 if all is ok
int getHashTablesListsInfo(HashTable *table, unsigned int *maxLength, double *averageLength);