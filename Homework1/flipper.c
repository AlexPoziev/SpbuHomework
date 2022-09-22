#include <stdio.h>
#include <stdlib.h>

void swap(int *firstNumber, int *secondNumber) { // Переворот двух элементов с временной переменной
    int temp = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = temp;
}

void arrayFlip(int array[], int startIndex, int endIndex) {
    for (int i = 0; i + startIndex <= (startIndex + endIndex) / 2; ++i) {    
        swap(&(array[startIndex + i]), &(array[endIndex - i])); 
    }
}

void arrayReplacement(int leftPart, int rightPart, int array[]) {
    const int arrayStart = 0;
    const int arrayEnd = leftPart + rightPart - 1;

    if (leftPart < 1 || rightPart < 1) {
        return;
    }

    arrayFlip(array, arrayStart, leftPart - 1);
    arrayFlip(array, leftPart, arrayEnd);
    arrayFlip(array, arrayStart, rightPart + leftPart - 1);
}

int main() {
    int m = 0;
    int n = 0;
   
    printf("Введите длинны массивов m, n через пробел: ");
    scanf("%d %d", &m, &n);

    int *arrayPointer = (int*)(calloc(m + n, sizeof(int)));

    printf("Поочередно введите значения массива: \n");
    for (int i = 0; i < m + n; ++i) {
        scanf("%d", &arrayPointer[i]);
    }

    arrayReplacement(m, n, arrayPointer);

    printf("Перевернутый массив: ");
    for(int i = 0; i < m + n; ++i) {
        printf("%d ", arrayPointer[i]);
    }

    free(arrayPointer);

    return 0;
}