#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int mostFrequentNumber(int array[], int arrayLength, int *errorCode) {
    unsigned int maxRow = 0;
    unsigned int recentCount = 1;
    int maxRowElement = 0;

    // создание копии массива, так как функция не всегда должна менять проверяемый массив
    int *sortedArray =  (int*)(calloc(arrayLength, sizeof(int)));
    if (sortedArray == NULL) {
        *errorCode = 1;
        return -1;
    }

    memcpy(sortedArray, array, sizeof(int) * arrayLength);
    qsortRecursion(0, arrayLength - 1, sortedArray);

    for (int i = 1; i < arrayLength; ++i) {
        if (sortedArray[i] == sortedArray[i - 1]) {
            ++recentCount;
        } else {
            if (maxRow < recentCount) {
                maxRowElement = sortedArray[i - 1];
                maxRow = recentCount;
            }

            recentCount = 1;
        }
    }

    int lastNumber = sortedArray[arrayLength - 1];

    free(sortedArray);

    return recentCount > maxRow ? lastNumber : maxRowElement;
}

void readFile(FILE *file, int *array, int arrayLength, int *errorCode) {
    int i = 0;
    for (; i < arrayLength && !(feof(file)); ++i) {
        int eofCheck = fscanf(file, "%d", &array[i]);
        if (!eofCheck) {
            *errorCode = -1;
            return;
        }

        // EOF check
        if (eofCheck == EOF) {
            *errorCode = -2;
            return;
        }
    }

    if (i != arrayLength) {
        *errorCode = -2;
        return;
    }
}

bool correctTest(void) {
    int firstCheck[10] = {0};
    int errorCode = 0;
    FILE *file = fopen("../test1.txt", "r");

    readFile(file, firstCheck, 10, &errorCode);
    fclose(file);
    int secondCheck[1] = {0};
    file = fopen("../test2.txt", "r");
    readFile(file, secondCheck, 1, &errorCode);
    fclose(file);
    int thirdCheck[5] = {0};
    file = fopen("../test3.txt", "r");
    readFile(file, thirdCheck, 10, &errorCode);
    fclose(file);

    return mostFrequentNumber(firstCheck, 10, &errorCode) == -6
        && mostFrequentNumber(secondCheck, 1, &errorCode) == 50
        && (mostFrequentNumber(thirdCheck, 5, &errorCode) == 100
        || mostFrequentNumber(thirdCheck, 5, &errorCode) == 15);
}

// first number in file is arrayLength
int main(int argc, char *argv[]) {
    if (argc >= 2) {
        if (!strcmp(argv[1], "--test")) {
            if (!correctTest()) {
                return 1;
            }
            
            return 0;
        }
    }

    FILE *file = fopen("../data.txt", "r");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    if (size == 0) {
        printf("File is empty\n");
        return 1;
    }

    fseek(file, 0, SEEK_SET);

    int arrayLength = 0;
    fscanf(file, "%d", &arrayLength);
    if (arrayLength < 1) {
        printf("Numbers count less or equal zero");
        fclose(file);

        return 2;
    }

    int *array = (int*)(calloc(arrayLength, sizeof(int)));
    if (array == NULL) {
        printf("Not enough memory");
        fclose(file);

        return 1;
    }

    int errorCode = 0;
    readFile(file, array, arrayLength, &errorCode);
    if (errorCode == -1) {
        printf("File contains not a number");
        free(array);
        fclose(file);

        return -1;
    }
    if (errorCode == -2) {
        printf("The written number of elements less than their actual number");
        free(array);
        fclose(file);

        return -2;
    }

    fclose(file);

    int mostFrequent = mostFrequentNumber(array, arrayLength, &errorCode);
    if (errorCode == 1) {
        printf("Not enough memory");
        free(array);

        return 1;
    }

    printf("Most frequent number: %d", mostFrequent);
    
    free(array);

    return 0;
}
