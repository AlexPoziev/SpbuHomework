#include "list.h"
#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    if (!hashTableTest() || !listTest()) {
        printf("Tests Failed");
        return 1;
    }

    HashTable *table = createHashTable(100);
    getFromFile("testSecond.txt", table);
    printHashTable(table);
    double test = getHashTableOccupancy(table);

    double check = 0;
    int testik = 0;

    getHashTablesListsInfo(table, &testik, &check);

    return 0;
}
