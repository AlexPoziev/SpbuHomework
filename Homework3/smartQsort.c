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
        array[i] = rand();
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

void semiQsort(int low, int high, int array[]) {
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

    if (!(low == high)) {
        swap(&array[low], &array[border]);;
    }
}

int main () {
    int array[10] = {6, 5, 2, 443434, 3, 1, 10, -10, 44444, 435155};
    semiQsort(2, 4, array);
    //semiQsort(10array);

    for (int i = 0; i < 10; ++i) {
        printf("%d ", array[i]);
    }

    return 0;
}