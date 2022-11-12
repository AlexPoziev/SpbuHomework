#include "hashTable.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct HashTable {
    List **hashTable;
    unsigned int hashTableSize;
} HashTable;

HashTable* createHashTable(unsigned int tableSize) {
    HashTable *temp = malloc(sizeof(HashTable));
    if (temp == NULL) {
        return NULL;
    }

    temp->hashTable = calloc(tableSize, sizeof(List*));
    if (temp->hashTable == NULL) {
        free(temp);
        return NULL;
    }

    temp->hashTableSize = tableSize;

    return temp;
}

// djb2 algorithm
unsigned int hashFunction(unsigned int tableSize, char *word) {
    unsigned long hash = 5381;

    int i = 0;
    while (word[i] != '\0') {
        hash = ((hash << 5) + hash) + (int)word[i];
        ++i;
    }

    return hash % tableSize;
}

int getFromFile(char *fileName, HashTable *table) {
    FILE *file = fopen(fileName, "r");
    // the longest word has 37 symbols
    char word[37];

    while (!feof(file)) {
        int eofCheck = fscanf(file, "%s", word);
        if (eofCheck == EOF) {
            fclose(file);
            return 0;
        }

        unsigned int hash = hashFunction(table->hashTableSize, word);
        if (table->hashTable[hash] == NULL) {
            table->hashTable[hash] = createList();
        }

        int errorCode = addWord(table->hashTable[hash], word);
        if (errorCode == 1) {
            return 1;
        }

        if (fgetc(file) == EOF) {
            return 0;
        }
    }

    fclose(file);

    return 0;
}

double getHashTableOccupancy(HashTable *table) {
    if (table == NULL) {
        return 0;
    }

    int occupancy = 0;
    for (int i = 0; i < table->hashTableSize; ++i) {
        if (table->hashTable[i] != NULL) {
            ++occupancy;
        }
    }

    return (double)occupancy / table->hashTableSize;
}

void printHashTable(HashTable *table) {
    if (table == NULL) {
        return;
    }

    for (int i = 0; i < table->hashTableSize; ++i) {
        printList(table->hashTable[i]);
    }
}

int getHashTablesListsInfo(HashTable *table, unsigned int *maxLength, double *averageLength) {
    if (table == NULL) {
        return -1;
    }

    *maxLength = 0;
    *averageLength = 0;
    unsigned int listCount = 0;

    for (int i = 0; i < table->hashTableSize; ++i) {
        if (table->hashTable[i] != NULL) {
            ++listCount;
            unsigned int currentNumber = getListLength(table->hashTable[i]);
            *maxLength = *maxLength >= currentNumber ? *maxLength : currentNumber;
            *averageLength += getListLength(table->hashTable[i]);
        }
    }

    *averageLength /= listCount;

    return 0;
}

void deleteHashTable(HashTable **table) {
    if (*table == NULL) {
        return;
    }

    for (int i = 0; i < (*table)->hashTableSize; ++i) {
        if ((*table)->hashTable[i] != NULL) {
            deleteList(&(*table)->hashTable[i]);
        }
    }

    free((*table)->hashTable);
    free(*table);
    *table = NULL;
}