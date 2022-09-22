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

void bubbleSort(int array[], const unsigned int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        bool anyAction = false;
        for (int j = arraySize - 1; j > i; --j) {
            if (array[j - 1] > array[j]) {
                anyAction = true;
                swap(&array[j - 1], &array[j]);
            }
        }
        if (!anyAction) {
            return;
        }
    }
}

void countingSort(int array[], const unsigned arraySize) {
    int max = array[0];
    int min = array[0];
    
    for (int i = 0; i < arraySize; ++i) {
        min = ((min > array[i]) ? array[i] : min);
        max = ((max < array[i]) ? array[i] : max);
    }
    
    int *numbersCount = (int*)(calloc(max - min + 1, sizeof(int)));
    if (numbersCount == NULL) {
        return;
    }
    
    for (int i = 0; i < arraySize; ++i) {
        ++numbersCount[array[i] - min];
    }
    
    int arrayIndex = 0;
    for (int i = 0; i <= max - min; ++i) {
        while (numbersCount[i] > 0) {
            array[arrayIndex] = i + min;
            ++arrayIndex;
            --numbersCount[i];
        }
    }
    
    free(numbersCount);
}

bool testModel(int array[], const int arraySize) {
    for (int i = 1; i < arraySize - 1; ++i) {
        if (!(array[i - 1] <= array[i])) {
            return false;
        }
    }
    return true;
}

bool correctTestBubble(void) {
    int arrayCheckFirst[1] = {5};
    int arrayCheckSecond[10] = {-1, 10, 5, -10, 3, 1000000, -141414, 0, -123, 444};
    int arrayCheckThird[100000] = {1};
    int arrayCheckFourth[5] = {1, 2, 3, 4, 5};
    int arraycheckFifth[6] = {-5, -10, -4, -100, -16, -19};
    
    bubbleSort(arrayCheckFirst, 1);
    bubbleSort(arrayCheckSecond, 10);
    bubbleSort(arrayCheckThird, 100000);
    bubbleSort(arrayCheckFourth, 5);
    bubbleSort(arraycheckFifth, 6);
    
    return testModel(arrayCheckFirst, 1) && testModel(arrayCheckSecond, 10) && testModel(arrayCheckThird, 100000) && testModel(arrayCheckFourth, 5) && testModel(arraycheckFifth, 6);
}

bool correctTestCount(void) {
    int arrayCheckFirst[1] = {5};
    int arrayCheckSecond[10] = {-1, 10, 5, -10, 3, 1000000, -141414, 0, -123, 444};
    int arrayCheckThird[100000] = {1};
    int arrayCheckFourth[5] = {1, 2, 3, 4, 5};
    int arraycheckFifth[6] = {-5, -10, -4, -100, -16, -19};
    
    countingSort(arrayCheckFirst, 1);
    countingSort(arrayCheckSecond, 10);
    countingSort(arrayCheckThird, 100000);
    countingSort(arrayCheckFourth, 5);
    countingSort(arraycheckFifth, 6);
    
    return testModel(arrayCheckFirst, 1) && testModel(arrayCheckSecond, 10) && testModel(arrayCheckThird, 100000) && testModel(arrayCheckFourth, 5) && testModel(arraycheckFifth, 6);
}

int main() {
    if (!correctTestBubble()) {
        printf("Bubble Tests Failed");
        return 1;
    }
    if (!correctTestCount()) {
        printf("Count Tests Failed");
        return 1;
    }
    
    const int arraySize = 100000;
    int arrayFirst[arraySize] = {0};
    int arraySecond[arraySize] = {0};
    
    randomArrayFilling(arraySize, arrayFirst);
    randomArrayFilling(arraySize, arraySecond);
    
    clock_t start_t = clock();
    bubbleSort(arrayFirst, arraySize);
    clock_t end_t = clock();
    printf("Bubble sort time: %f seconds\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    start_t = clock();
    countingSort(arraySecond, arraySize);
    end_t = clock();
    printf("Count sort time: %f seconds\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    
    return 0;
}
