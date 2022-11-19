#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool testCase(int array[], int firstNumber, int arraySize) {//тест на правильное расположение, все числа до первого должны быть меньше, дальше - больше либо равно
    unsigned int i = 0;
    
    for (i = 0; array[i] != firstNumber; ++i) {
        if (array[i] >= firstNumber) {
            return false;
        }
    }
    for (; i < arraySize; ++i) {
        if (array[i] < firstNumber) {
            return false;
        }
    }
    return arraySize >= 1;
}

void randomArrayFilling(unsigned int arraySize, int array[]) {
    if (arraySize < 1) {
        return;
    }

    srand((unsigned)time(0));
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 50000; //уменьшение чисел для лучшего восприятия, но можно убрать или вообще запрашивать в функцию
    }
} 

void swap(int* first, int*second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void semiQsort(unsigned int arraySize, int array[]) {
    if (arraySize < 1) {
        return;
    }
    
    const int startArray = 0;
    const int firstNumber = array[0];
    //граница, для первого числа
    int border = arraySize - 1;
    for (int i = 1; i < border; ++i) {
        if (array[i] >= firstNumber) {
            //чтобы не выкинуть с правой части границы число, удовлетворяющее условию
            while (array[border] >= firstNumber && i < border) {
                --border;
            }
            swap(&array[i], &array[border]);
            --border;
        }
    }
    //проверка, чтобы при размере 1 программа не нахватала лишних данных
    if (!(arraySize == 1)) {
        swap(&array[startArray], &array[border]);
    }
}

bool correctTest(void) {
    int arrayCheckFirst[1] = {5};
    int arrayCheckSecond[10] = {-1, 10, 5, -10, 3, 1000000, -141414, 0, -123, 444};
    int arrayCheckThird[100000] = {1};
    int arrayCheckFourth[5] = {100000, 1, 2, 3, 4};
        
    semiQsort(1, arrayCheckFirst);
    semiQsort(10, arrayCheckSecond);
    semiQsort(10000, arrayCheckThird);
    semiQsort(5, arrayCheckFourth);
        
    return testCase(arrayCheckFirst, 5, 1) && testCase(arrayCheckSecond, -1, 10) && testCase(arrayCheckThird, 0, 10000) && testCase(arrayCheckFourth, 100000, 5);
}

int main() {
    if (!correctTest()) {
        printf("Tests Failed");
        return 1;
    }
    
    printf("Enter a count of numbers, except zero: ");
    //Делаю тип int, чтобы проверить на отрицательные и ноль
    int arraySize = 0;
    scanf("%d", &arraySize);
    while (arraySize < 1) {
        printf("Count of numbers cannot be negative or zero, repeat input: ");
        scanf("%d", &arraySize);
    }
    
    int *array = (int*)(calloc(arraySize, sizeof(int)));
    if (array == NULL) {
        printf("Not enough memory");
        return 1;
    }
    
    randomArrayFilling(arraySize, array);
    const int firstNumber = array[0];
    semiQsort(arraySize, array);
    
    printf("The first number: %d \n", firstNumber);
    printf("Semi-sorted array: ");
    for (int i = 0; i < arraySize; ++i) {
        printf("%d ", array[i]);
    }
    
    free(array);
    
    return 0;
}
