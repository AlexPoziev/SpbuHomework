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

bool correctTest(void) {


    return mostFrequentNumber(arrayFirst, 1) == 1000 && mostFrequentNumber(arraySecond, 8) == 10 && mostFrequentNumber(arrayThird, 3) == 1 || mostFrequentNumber(arrayThird, 3) == 2 || mostFrequentNumber(arrayThird, 3) == 3 && mostFrequentNumber(arrayFourth, 3) == 0;
}

int main() {
    /*if (!correctTest()) {
        printf("Test Failed");
        return 1;
    }

    printf("Enter a count of numbers, except zero: ");
    int arrayLength = 0;
    scanf("%d", &arrayLength);
    while (arrayLength < 1) {
        printf("Count of numbers cannot be negative or zero, repeat input: ");
        scanf("%d", &arrayLength);
    }

    int* array = (int*)(calloc(arrayLength, sizeof(int)));
    if (array == NULL) {
        printf("Not enough memory");
        return 1;
    }

    printf("Enter numbers: \n");
    for (int i = 0; i < arrayLength; ++i) {
        bool isString = scanf("%d", (&array[i]));
        while (!isString) {
            printf("Entered value isn't number, repeat enter: \n");
            fflush(stdin);
            isString = scanf("%d", &array[i]);
        }
    }

    printf("The most frequent number in array: %d \n", mostFrequentNumber(array, arrayLength));


    free(array);
*/
    FILE *file = fopen("data.txt", "r");

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