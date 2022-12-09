#include "hashTable.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct HashTable {
    List **hashTable;
    unsigned int hashTableSize;
} HashTable;

HashTable* createHashTable(void) {
    const int8_t baseHashTableSize = 2;

    HashTable *temp = malloc(sizeof(HashTable));
    if (temp == NULL) {
        return NULL;
    }

    temp->hashTable = calloc(baseHashTableSize, sizeof(List*));
    if (temp->hashTable == NULL) {
        free(temp);
        return NULL;
    }

    temp->hashTableSize = baseHashTableSize;

    return temp;
}

bool isFullOccupancy(HashTable *hashTable) {
    for (int i = 0; i < hashTable->hashTableSize; ++i) {
        if (hashTable->hashTable[i] == NULL) {
            return false;
        }
    }

    return true;
}

// djb2 algorithm
unsigned int hashFunction(unsigned int tableSize, const char *word) {
    unsigned long hash = 5381;

    int i = 0;
    while (word[i] != '\0') {
        hash = ((hash << 5) + hash) + (int)word[i];
        ++i;
    }

    return hash % tableSize;
}

int hashTableResize(HashTable *hashTable);

int getFromFile(char *fileName, HashTable *table) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return -1;
    }

    // the longest word has 37 symbols
    char word[38] = {0};

    while (!feof(file)) {
        int eofCheck = fscanf(file, "%s", word);
        if (eofCheck == EOF) {
            fclose(file);
            return 0;
        }

        unsigned int hash = hashFunction(table->hashTableSize, word);
        if (table->hashTable[hash] == NULL) {
            table->hashTable[hash] = createList();
            if (table->hashTable == NULL) {
                return 1;
            }
        }

        int errorCode = addWord(table->hashTable[hash], word);
        if (errorCode == 1) {
            fclose(file);
            return 1;
        }

        if (!feof(file)) {
            double occupancyRate = getHashTableOccupancy(table);
            const double delta = 0.000001;
            if ((1 - occupancyRate) < delta) {
                if (hashTableResize(table)) {
                    return 1;
                }
            }
        }

        if (fgetc(file) == EOF) {
            fclose(file);
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

    unsigned int occupancy = 0;
    for (int i = 0; i < table->hashTableSize; ++i) {
        if (table->hashTable[i] != NULL) {
            occupancy += getListLength(table->hashTable[i]);
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

// returns 0 if all is ok
// returns 1 if not enough memory
int hashTableResize(HashTable *hashTable) {
    List **tempHashTable = calloc(hashTable->hashTableSize * 2, sizeof(List*));
    if (tempHashTable == NULL) {
        return 1;
    }

    int errorCode = 0;

    for (int i = 0; i < hashTable->hashTableSize; ++i) {
        while (hashTable->hashTable[i] != NULL) {
            List *tempList = getFirst(&hashTable->hashTable[i], &errorCode);
            if (errorCode == 1) {
                for (int j = 0; i < hashTable->hashTableSize * 2; ++j) {
                    deleteList(&tempHashTable[i]);
                }

                free(tempHashTable);
                
                return 1;
            }

            char *tempString = getFirstWord(tempList);
            unsigned int hash = hashFunction(hashTable->hashTableSize * 2, tempString);
            if (tempHashTable[hash] == NULL) {
                tempHashTable[hash] = tempList;
            } else {
                putList(&tempHashTable[hash], &tempList);
            }
        }
    }

    free(hashTable->hashTable);

    hashTable->hashTable = tempHashTable;
    hashTable->hashTableSize *= 2;

    return 0;
}

unsigned int getFrequencyByWord(HashTable *table, char *word, int *errorCode) {
    if (table == NULL || word == NULL) {
        *errorCode = -1;
        return 0;
    }

    unsigned int hashValue = hashFunction(table->hashTableSize, word);
    ListElement *element = getFirstListElement(table->hashTable[hashValue]);
    while (element != NULL) {
        if (!strcmp(word, getElementWord(element))) {
            return getElementFrequency(element, errorCode);
        }

        element = getNextListElement(element);
    }

    return 0;
}

unsigned int getHashTableSize(HashTable *table) {
    if (table == NULL) {
        return 0;
    }

    return table->hashTableSize;
}

int addValueToHashTable(HashTable *table, char *value) {
    if (table == NULL || value == NULL) {
        return -1;
    }

    unsigned int hash = hashFunction(table->hashTableSize, value);
    if (table->hashTable[hash] == NULL) {
        table->hashTable[hash] = createList();
        if (table->hashTable == NULL) {
            return 1;
        }
    }

    int errorCode = addWord(table->hashTable[hash], value);
    if (errorCode == 1) {
        return 1;
    }

    const double delta = 0.0001;
    if ((1 - getHashTableOccupancy(table)) < delta) {
        hashTableResize(table);
    }

    return 0;
}