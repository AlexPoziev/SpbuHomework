#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void *x_void, const void *y_void) {
    int x = *(int *)x_void;
    int y = *(int *)y_void;
    
    return x - y;
}

int mostFrequent(int array[], int arrayLenght) {
    unsigned int maxRow = 0;
    unsigned int recentCount = 1;
    int maxRowElement = 0;

    for (int i = 1; i < arrayLenght; ++i) {
        if (array[i] == array[i - 1]) {
            ++recentCount;
        } else {
            if (maxRow < recentCount) {
                maxRowElement = array[i - 1];
                maxRow = recentCount;
            }
            recentCount = 1;
        }
    }
    
    return recentCount > maxRow ? array[arrayLenght - 1] : maxRowElement;
}

int main() {
    int array[8] = {1,1,2,2,2,3,3,3};
    int check = mostFrequent(array, 8);
    printf("%d", check);
    return 0;
}