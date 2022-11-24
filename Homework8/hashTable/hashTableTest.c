#include "hashTableTest.h"
#include "hashTable.h"
#include <stdlib.h>

bool createHashTableTest(void) {
    HashTable *table = createHashTable();
    if (table == NULL) {
        return false;
    }

    bool test = table != NULL && table->hashTableSize == 2;

    deleteHashTable(&table);

    return test;
}