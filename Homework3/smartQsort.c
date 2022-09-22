#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void randomArrayFilling(unsigned int arraySize, int array[]) {
    if (arraySize < 1) {
        return;
    }
    
    srand((unsigned)time(0));
    
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 50000;
    }
}

void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void insertionSort(int low, int high, int array[]) {
    for (int i = low; i <= high; ++i) {
        int j = i;
        while (j > low && array[j - 1] > array[j]) {
            swap(&array[j - 1] , &array[j]);
            --j;
        }
    }
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

        if (high - low < 9) {
            insertionSort(low, high, array);
        } else {
            int border = semiQsort(low, high, array);
            qsortRecursion(low, border - 1, array);
            qsortRecursion(border + 1, high, array);
        }
    }
}

bool testModel(int array[], const int arraySize, int *differentNumbers) {
    *differentNumbers = 0;
    for (int i = 1; i < arraySize - 1; ++i) {
        if (array[i - 1] != array[i]) {
            ++(*differentNumbers);
        }
        if (!(array[i - 1] <= array[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("Enter a count of numbers, except zero: ");
    unsigned int arraySize = 0;
    scanf("%d", &arraySize);
    while (arraySize < 1) {
        printf("Count of numbers cannot be negative or zero, repeat input: ");
        scanf("%d", &arraySize);
    }

    int *array = (int*)(calloc(arraySize, sizeof(int)));
    if (array == NULL) {
        printf("Not enough memory");
        return 1;
    }
    randomArrayFilling(arraySize, array);

    qsortRecursion(0, arraySize - 1, array);
    printf("Sorted array: ");
    for (int i = 0; i < arraySize; ++i) {
        printf("%d ", array[i]);
    }

    free(array);

    return 0;
}