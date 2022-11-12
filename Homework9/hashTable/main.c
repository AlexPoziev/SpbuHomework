#include "list.h"
#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    if (!hashTableTest() || !listTest()) {
        printf("Tests Failed");
        return 1;
    }
    printf("Print approximate number of words, larger than zero: ");
    unsigned int tableSize = 0;
    int errorCode = scanf("%u", &tableSize);
    while (errorCode <= 0) {
        fflush(stdin);
        printf("it's string, please repeat input: ");
        errorCode = scanf("%u", &tableSize);
    }

    HashTable *table = createHashTable((unsigned int)(tableSize * 1.3));
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
