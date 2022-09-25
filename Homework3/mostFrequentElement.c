#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

int semiQsort(int low, int high, int array[]) {
    const int firstNumber = array[low];
    int border = high;

    for (int i = low + 1; i < border; ++i) {
        if (array[i] >= firstNumber) {
            while (array[border] >= firstNumber && i < border) {
                --border;
            }
            swap(&array[i], &array[border]);
            --border;
        }
    }

    if (firstNumber < array[border]) {
        --border;
    }

    if (!(low == high)) {
        swap(&array[low], &array[border]);;
    }

    return border;
}

void qsortRecursion(int low, int high, int array[]) {
    if (low < high) {
        int border = semiQsort(low, high, array);
        qsortRecursion(low, border - 1, array);
        qsortRecursion(border + 1, high, array);
    }
}

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
    int arrayFirst[1] = {1000};
    int arraySecond[8] = {-2, 10, 5, 1, 10, 10, -1, 1};
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
        while (!isString) {
            printf("Entered value isn't number, repeat enter: \n");
            fflush(stdin);
            isString = scanf("%d", &array[i]);
        }
    }

    printf("The most frequent number in array: %d \n", mostFrequentNumber(array, arrayLength));

    return 0;
}