#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void fillRandomArray(unsigned int arraySize, int array[]) {
    if (arraySize < 1) {
        return;
    }
    
    srand((unsigned)time(NULL));
    
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

int partition(int low, int high, int array[]) {
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

    if (low != high) {
        swap(&array[low], &array[border]);
    }

    return border;
}

void qsortRecursion(int low, int high, int array[]) {
    if (low < high) {
        if (high - low < 9) {
            insertionSort(low, high, array);
        } else {
            int border = partition(low, high, array);
            qsortRecursion(low, border - 1, array);
            qsortRecursion(border + 1, high, array);
        }
    }
}

bool testModel(int array[], const int arraySize, int differentNumbers) {
    int sortedDifferentNumbers = 1;
    for (int i = 1; i < arraySize; ++i) {
        if (array[i - 1] != array[i]) {
            ++sortedDifferentNumbers;
        }
        if (!(array[i - 1] <= array[i])) {
            return false;
        }
    }
    return differentNumbers == sortedDifferentNumbers;
}

bool correctTest(void) {
    const int low = 0;
    int arrayCheckFirst[1] = {5};
    int arrayCheckSecond[10] = {-1, 10, 5, -10, -10, 1000000, -141414, 0, -123, 444};
    int arrayCheckThird[5] = {1, 2, 3, 4, 5};
    int arrayCheckFourth[6] = {-5, -10, -4, -100, -16, -16};
    //В моем алгоритме по semiSort функция с данным массивом работала неверно
    int arrayCheckFifth[10] = {6, 5, 2, 443434, 3, 1, 10, -10, 44444, 435155};
    int arrayCheckSixth[10000] = {1};
    
    qsortRecursion(low, 0, arrayCheckFirst);
    qsortRecursion(low, 9, arrayCheckSecond);
    qsortRecursion(low, 4, arrayCheckThird);
    qsortRecursion(low, 5, arrayCheckFourth);
    qsortRecursion(low, 9, arrayCheckFifth);
    qsortRecursion(low, 9999, arrayCheckSixth);
    
    return testModel(arrayCheckFirst, 1, 1) && testModel(arrayCheckSecond, 10, 9) && testModel(arrayCheckThird, 5, 5) && testModel(arrayCheckFourth, 6, 5) && testModel(arrayCheckFifth, 10, 10) && testModel(arrayCheckSixth, 10000, 2);
}

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        if (!strcmp(argv[1], "--test")) {
            if (!correctTest()) {
                return 1;
            }
            
            return 0;
        }
    }

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
    fillRandomArray(arraySize, array);

    qsortRecursion(0, arraySize - 1, array);
    printf("Sorted array: ");
    for (int i = 0; i < arraySize; ++i) {
        printf("%d ", array[i]);
    }

    free(array);

    return 0;
}
