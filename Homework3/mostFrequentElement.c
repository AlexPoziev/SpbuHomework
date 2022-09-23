#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int compare(const void *x_void, const void *y_void) {
    int x = *(int*)x_void;
    int y = *(int*)y_void;
    
    return x - y;
}

int mostFrequentNumber(int array[], int arrayLength) {
    unsigned int maxRow = 0;
    unsigned int recentCount = 1;
    int maxRowElement = 0;
    
    //создание копии массива, так как функция не всегда должна менять проверяемый массив
    int *sortedArray =  (int *)(calloc(arrayLength, sizeof(int)));
    memcpy(sortedArray, array, sizeof(int) * arrayLength);
    qsort(sortedArray, arrayLength, sizeof(int), compare);

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
    
    return recentCount > maxRow ? sortedArray[arrayLength - 1] : maxRowElement;
}

bool correctTest(void) {
    int arrayFirst[1] = {1000};
    int arraySecond[8] = {1, 10, 5, 1, 10, 10, -1, -2};
    int arrayThird[3] = {1, 2, 3};
    int arrayFourth[3] = {0, 0, 0};

    return mostFrequentNumber(arrayFirst, 1) == 1000 && mostFrequentNumber(arraySecond, 8) == 10 && mostFrequentNumber(arrayThird, 3) == 1 || mostFrequentNumber(arrayThird, 3) == 2 || mostFrequentNumber(arrayThird, 3) == 3 && mostFrequentNumber(arrayFourth, 3) == 0;
}

int main() {
    if (!correctTest()) {
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

    printf("Enter number: \n");
    for (int i = 0; i < arrayLength; ++i) {
        bool isString = scanf("%d", (&array[i]));
        while (!isString) { // проверка, лежит в переменной тип int или строка
            printf("Entered value isn't number, repeat enter: \n");
            fflush(stdin);//очистка буфера
            isString = scanf("%d", &array[i]);
        }
    }

    printf("The most frequent number in array: %d \n", mostFrequentNumber(array, arrayLength));

    return 0;
}