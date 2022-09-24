#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
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

    int *sortedArray =  (int*)(calloc(arraySize, sizeof(int)));
    memcpy(sortedArray, array, sizeof(int) * arraySize);
    qsortRecursion(0, arraySize - 1, sortedArray);

    while (low <= high) {
        int middle = (high + low) / 2;
            
        if (sortedArray[middle] == number) {
            return true;
        }
        (sortedArray[middle] > number) ? (high = middle - 1) : (low = middle + 1);
    }

    return false;
}

bool correctTest(void) {
    int arrayFirst[8] = {9, 3535, -12414, 44434, 1111, 0, 0, 0};
    int arraySecond[1] = {10};

    return search(-12414, arrayFirst, 8) && search(44434, arrayFirst, 8) && search(9, arrayFirst, 8) && search(10, arraySecond, 1);
}

bool incorrectTest(void) {
    int arrayFirst[8] = {9, 3535, -12414, 44434, 1111, 0, 0, 0};
    int arraySecond[1] = {10};

    return !search(-12444, arrayFirst, 8) && !search(44433, arrayFirst, 8) && !search(8, arrayFirst, 8) && !search(9, arraySecond, 1);
}

int main() {

    return 0;
}