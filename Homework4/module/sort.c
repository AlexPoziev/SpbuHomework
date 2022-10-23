#include "sort.h"
#include <stdlib.h>

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

// realization of partition
int partition(int low, int high, int array[]) {
    int middle = (low + high) / 2;

    int tempArray[3] = {0};

    tempArray[0] = array[low];
    tempArray[1] = array[middle];
    tempArray[2] = array[high];
    insertionSort(0, 2, tempArray);

    array[0] = tempArray[0];
    array[middle] = tempArray[1];
    array[high] = tempArray[2];

    swap(&array[1], &array[middle]);
    int border = high - 1;
    const int firstNumber = array[low + 1];

    for (int i = low + 2; i < border; ++i) {
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
        swap(&array[low + 1], &array[border]);;
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
