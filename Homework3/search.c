#include <stdio.h>
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

int main() {
    
    return 0;
}