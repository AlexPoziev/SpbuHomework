#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int zeroCount(int arraySize, int array[]) { //{2}
    int zeroes = 0;
    for (int i = 0; i < arraySize; ++i) {
        if (array[i] == 0) {
            ++zeroes;
        }
    }
    
    return zeroes;
}

int main() {
    int arrayLength = 0;

    printf("Введите длину массива: ");
    scanf("%d", &arrayLength);

    int* arrayPointer = (int*)(calloc(arrayLength, sizeof(int)));
    if (arrayPointer == NULL) {
        printf("Недостаточно памяти для выполнения задания");
        return 1;
    }

    printf("Поочередно введите значения массива: \n");
    for (int i = 0; i < arrayLength; ++i) {
        int isString = scanf("%d", (&arrayPointer[i]));
        while (isString == 0) { // проверка, лежит в переменной тип int или строка
            printf("Введенное значение не является числом, произведите ввод снова: \n");
            fflush(stdin);//очистка буфера
            isString = scanf("%d", &arrayPointer[i]);
        }
    }
    printf("Количество вхождений нуля в массив: %d", zeroCount(arrayLength, arrayPointer));

    free(arrayPointer);

    return 0;
}

