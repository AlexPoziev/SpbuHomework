#pragma once

typedef struct HashTable HashTable;

// create Hash table, get hash table size, need to check for NULL
HashTable* createHashTable(unsigned int tableSize);

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