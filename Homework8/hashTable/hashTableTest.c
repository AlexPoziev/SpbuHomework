#include "hashTableTest.h"
#include "hashTable.h"
#include <stdlib.h>

bool createHashTableTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }

    bool test = table != NULL && getHashTableSize(table) == 2;

    deleteHashTable(&table);

    return test;
}

bool getFromFileTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }

    int errorCode = getFromFile("firstTest.txt", table);
    if (errorCode == 1) {
        free(table);
        return false;
    }

    bool firstTest = getFrequencyByWord(table, "just", &errorCode) == 1;
    bool secondTest = getFrequencyByWord(table, "for", &errorCode) == 2;
    bool thirdTest = getFrequencyByWord(table, "test", &errorCode) == 1;
    bool fourthTest = getFrequencyByWord(table, "text", &errorCode) == 1;
    bool fifthTest = getFrequencyByWord(table, "Leoric", &errorCode) == 0;


    deleteHashTable(&table);

    return firstTest && secondTest && thirdTest && fourthTest
           && fifthTest;
}

bool getHashTableOccupancyTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }
    const double delta = 0.00001;

    bool testFirst = (getHashTableOccupancy(table) - 0) < delta;

    int errorCode = getFromFile("secondTest.txt", table);
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

    int errorCode = getFromFile("secondTest.txt", table);
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

    int errorCode = getFromFile("secondTest.txt", table);
    if (errorCode == 1) {
        free(table);
        return false;
    }

    deleteHashTable(&table);

    return table == NULL;
}

bool getFrequencyByWordTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }

    int errorCode = getFromFile("secondTest.txt", table);
    if (errorCode == 1) {
        free(table);
        return false;
    }

    bool firstTest = getFrequencyByWord(table, "Vestibulum", &errorCode) == 2;
    bool secondTest = getFrequencyByWord(table, "venenatis", &errorCode) == 3;
    bool thirdTest = getFrequencyByWord(table, "porta", &errorCode) == 1;
    bool fourthTest = getFrequencyByWord(table,"Math-n-Mech", &errorCode) == 0;

    deleteHashTable(&table);

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool getHashTableSizeTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }

    int errorCode = getFromFile("secondTest.txt", table);
    if (errorCode == 1) {
        free(table);
        return false;
    }

    bool test = getHashTableSize(table) == 256;

    deleteHashTable(&table);

    return test;
}

bool hashTableTest(void) {
    return createHashTableTest() && getFromFileTest() && getHashTableOccupancyTest()
        && getHashTablesListsInfoTest() && deleteHashTableTest() && getFrequencyByWordTest()
        && getHashTableSizeTest();
}

