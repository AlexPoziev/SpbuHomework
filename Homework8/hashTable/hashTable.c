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
    char word[37] = {0};

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
                hashTableResize(table);
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
                return 1;
            }

            char *tempString = getFirstWord(tempList);
            unsigned int hash = hashFunction(hashTable->hashTableSize * 2, tempString);
            if (tempHashTable[hash] == NULL) {
                tempHashTable[hash] = tempList;
            } else {
                putList(tempHashTable[hash], &tempList);
            }
        }
    }

    free(hashTable->hashTable);

    hashTable->hashTable = tempHashTable;
    hashTable->hashTableSize *= 2;

    return 0;
}

// =========================tests=========================

bool createHashTableTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }

    bool test = table != NULL && table->hashTableSize == 2;

    deleteHashTable(&table);

    return test;
}

bool getFromFileTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }

    int errorCode = getFromFile("testFirst.txt", table);
    if (errorCode == 1) {
        free(table);
        return false;
    }

    bool firstTest = !strcmp("task", getFirstWord(table->hashTable[0]));
    bool secondTest = table->hashTable[1] == NULL;
    bool thirdTest = !strcmp("text", getFirstWord(table->hashTable[2]));
    bool fourthTest = !strcmp("just", getFirstWord(table->hashTable[3]));
    bool fifthTest = table->hashTableSize == 8;
    bool sixthTest = !strcmp("for", getFirstWord(table->hashTable[4]));
    bool seventhTest = !strcmp("test", getFirstWord(table->hashTable[5]));
    bool eighthTest = !strcmp("new", getFirstWord(table->hashTable[7]));
    bool ninthTest = table->hashTable[6] == NULL;

    deleteHashTable(&table);

    return firstTest && secondTest && thirdTest && fourthTest
        && fifthTest && sixthTest && seventhTest && eighthTest
        && ninthTest;
}

bool getHashTableOccupancyTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }
    const double delta = 0.00001;

    bool testFirst = (getHashTableOccupancy(table) - 0) < delta;

    int errorCode = getFromFile("testSecond.txt", table);
    if (errorCode == 1) {
        free(table);
        return false;
    }

    bool secondTest = (getHashTableOccupancy(table) - 0.902344) < delta;

    deleteHashTable(&table);

    return testFirst && secondTest;
}

bool getHashTablesListsInfoTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }
    const double delta = 0.01;

    int errorCode = getFromFile("testSecond.txt", table);
    if (errorCode == 1) {
        free(table);
        return false;
    }

    double average = 0;
    unsigned int max = 0;

    getHashTablesListsInfo(table, &max, &average);

    bool test = max == 4 && average - 1.5 < delta;

    deleteHashTable(&table);

    return test;
}

bool deleteHashTableTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }

    int errorCode = getFromFile("testSecond.txt", table);
    if (errorCode == 1) {
        free(table);
        return false;
    }

    deleteHashTable(&table);

    return table == NULL;
}

bool hashTableTest(void) {
    return createHashTableTest() && getFromFileTest() && getHashTableOccupancyTest()
    && getHashTablesListsInfoTest() && deleteHashTableTest();
}