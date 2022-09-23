#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int compare(const void *x_void, const void *y_void) {
    int x = *(int *)x_void;
    int y = *(int *)y_void;
    
    return x - y;
}

int mostFrequent(int array[], int arrayLength) {
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

int main() {
    int array[5] = {5, 2, 3, 1, 3};
    int check = mostFrequent(array, 5);
    printf("%d", check);
    return 0;
}