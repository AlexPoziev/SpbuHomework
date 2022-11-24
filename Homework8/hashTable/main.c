#include "listTest.h"
#include "hashTable.h"
#include "hashTableTest.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    if (!hashTableTest() || !listTest()) {
        printf("Tests Failed");
        return 1;
    }

    int errorCode = 0;
    HashTable *table = createHashTable();
    if (table == NULL) {
        printf("Not enough memory");
        return 1;
    }

    printf("Print name of file, with length less than 20: ");
    char fileName[20] = {0};
    scanf("%s", fileName);

    errorCode = getFromFile(fileName, table);
    if (errorCode == -1) {
        printf("No file with this name");
        return 0;
    }
    if (errorCode == 1) {
        deleteHashTable(&table);
        return 1;
    }

    printHashTable(table);

    printf("Coefficient of occupancy in table: %g \n", getHashTableOccupancy(table));

    double averageListLength = 0.0;
    unsigned int maxListLength = 0;

    getHashTablesListsInfo(table, &maxListLength, &averageListLength);
    printf("Max length of list in hash table: %d \n", maxListLength);
    printf("Average length of lists in hash table: %g", averageListLength);

    deleteHashTable(&table);

    return 0;
}
