#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int mostFrequentNumber(int array[], int arrayLength) {
    unsigned int maxRow = 0;
    unsigned int recentCount = 1;
    int maxRowElement = 0;

    //создание копии массива, так как функция не всегда должна менять проверяемый массив
    int *sortedArray =  (int*)(calloc(arrayLength, sizeof(int)));
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

void readFile(FILE *file, int *array, int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        fscanf(file, "%d", &array[i]);
    }
}

bool correctTest(void) {
    int firstCheck[10] = {0};
    FILE *file = fopen("test1.txt", "r");
    readFile(file, firstCheck, 10);
    fclose(file);
    int secondCheck[1] = {0};
    file = fopen("test2.txt", "r");
    readFile(file, secondCheck, 1);
    fclose(file);
    int thirdCheck[5] = {0};
    file = fopen("test3.txt", "r");
    readFile(file, thirdCheck, 10);
    fclose(file);

    return mostFrequentNumber(firstCheck, 10) == -6 && mostFrequentNumber(secondCheck, 1) == 50 && (mostFrequentNumber(thirdCheck, 5) == 100 || mostFrequentNumber(thirdCheck, 5) == 15);
}

//first number in file is arrayLength
int main() {
    if (!correctTest()) {
        printf("Test Failed");
        return 1;
    }
    FILE *file = fopen("data.txt", "r");
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
        return 2;
    }

    int *array = (int*)(calloc(arrayLength, sizeof(int)));
    if (array == NULL) {
        printf("Not enough memory");
        return 1;
    }

    int i = 0;
    for (; i < arrayLength && !(feof(file)); ++i) {
        if (!(fscanf(file, "%d", &array[i]))) {
            printf("Not a number");
            return 2;
        }
    }
    if (i != arrayLength) {
        printf("Not enough numbers");
        return 2;
    }

    fclose(file);
    printf("Most frequent number: %d", mostFrequentNumber(array, arrayLength));
    free(array);

    return 0;
}