#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = *first;
}

void randomArrayFilling(unsigned int arraySize, int array[]) {
    if (arraySize < 1) {
        return;
    }
    
    srand((unsigned)time(0));
    
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand();
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
            int border = semiQsort(low, high, array);
            qsortRecursion(low, border - 1, array);
            qsortRecursion(border + 1, high, array);
    }
}

bool search(int number, int array[], int arraySize) { 
    int low = 0;
    int high = arraySize - 1;

    while (low <= high) {
        int middle = (high + low) / 2;
            
        if (array[middle] == number) {
            return true;
        }
        (array[middle] > number) ? (high = middle - 1) : (low = middle + 1);
    }

    return false;
}

int main() {
    int array[6] = {1, 2, 3, 4, 5, 6};
    printf("%d ", search(6, array, 6));
    return 0;
}