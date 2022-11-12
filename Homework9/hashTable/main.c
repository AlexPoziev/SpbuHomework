#include "list.h"
#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    HashTable *table = createHashTable(10);
    getFromFile("test.txt", table);
    int occupancy = getHashTableOccupancy(table);
    printf("%d", occupancy);

    printHashTable(table);
    double check = 0;
    int test = 0;
    getHashTablesListsInfo(table, &test, &check);

    return 0;
}
