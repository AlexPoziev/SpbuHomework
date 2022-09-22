#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void insertionSort(int array[], int low, int high) {
    for (int i = low; i <= high; ++i) {
        int j = i;
        while (j > low && array[j - 1] > array[j]) {
            swap(&array[j - 1] , &array[j]);
            --j;
        }
    }
}

int main () {

    return 0;
}