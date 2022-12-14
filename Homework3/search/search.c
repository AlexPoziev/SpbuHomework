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

void insertionSort(int low, int high, int array[]) {
    for (int i = low; i <= high; ++i) {
        int j = i;
        while (j > low && array[j - 1] > array[j]) {
            swap(&array[j - 1] , &array[j]);
            --j;
        }
    }
}

void fillRandomArray(unsigned int arraySize, int array[], unsigned int callTime) {
    if (arraySize < 1) {
        return;
    }
    
    srand((unsigned)time(NULL) + callTime);
    
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 10;
    }
}

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

bool search(int number, int array[], int arraySize) { 
    int low = 0;
    int high = arraySize - 1;

    int *sortedArray =  (int*)(calloc(arraySize, sizeof(int)));
    memcpy(sortedArray, array, sizeof(int) * arraySize);
    qsortRecursion(0, arraySize - 1, sortedArray);

    while (low <= high) {
        int middle = (high + low) / 2;
            
        if (sortedArray[middle] == number) {
            free(sortedArray);
            return true;
        }
        (sortedArray[middle] > number) ? (high = middle - 1) : (low = middle + 1);
    }

    free(sortedArray);

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

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        if (!strcmp(argv[1], "--test")) {
            if (!correctTest() || !incorrectTest()) {
                return 1;
            }
            
            return 0;
        }
    }

    printf("Enter main array size greater than zero: ");
    int arraySizeMain = 0;
    scanf("%d", &arraySizeMain);
    while (arraySizeMain < 1) {
        printf("Numbers count must be greater than zero: \n");
        scanf("%d", &arraySizeMain);
    }

    printf("Enter search array size greater than zero: ");
    int arraySizeSearch = 0;
    scanf("%d", &arraySizeSearch);
    while (arraySizeSearch < 1) {
        printf("Numbers count must be greater than zero: \n");
        scanf("%d", &arraySizeSearch);
    }

    int *arrayMain = (int*)(calloc(arraySizeMain, sizeof(int)));
    fillRandomArray(arraySizeMain, arrayMain, 1);
    int *arraySearch = (int*)(calloc(arraySizeSearch, sizeof(int)));
    fillRandomArray(arraySizeSearch, arraySearch, 2);

    printf("Main array: ");
    for (int i = 0; i < arraySizeMain; ++i) {
        printf("%d ", arrayMain[i]);
    }
    printf("\n");
    for (int i = 0; i < arraySizeSearch; ++i) {
        printf("%d %s in array \n", arraySearch[i], (search(arraySearch[i], arrayMain, arraySizeMain)) ? "contained" : "not contained");
    }

    free(arrayMain);
    free(arraySearch);

    return 0;
}
