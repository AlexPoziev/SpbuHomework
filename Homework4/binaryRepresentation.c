#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>

void printArray(short *array, unsigned int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d", array[i]);
    }
    printf("\n");
}

short* columnAddition(short *first, short *second, unsigned numberDigits) {
    short* sum = (short*)(calloc(numberDigits, sizeof(short)));
    if (sum == NULL) {
        return NULL;
    }
    bool anyRemainder = false;

    for (int i = numberDigits - 1; i >= 0; --i) {
        if (first[i] && second[i]) {
            sum[i] = anyRemainder ? 1 : 0;
            anyRemainder = true;
        } else {
            if (anyRemainder && (first[i] || second[i])) {
                sum[i] = 0;
                anyRemainder = true;
            } else {
                sum[i] = anyRemainder || first[i] || second[i]
                ? (sum[i] = 1)
                : (sum[i] = 0);
                anyRemainder = false;
            }
        }
    }
    return sum;
}

void binaryRepresentation(int number, unsigned int numberDigits, short* representation) {
    number = number > 0 ? number : (int)pow(2, numberDigits) + number;

    for (int i = numberDigits - 1; i >= 0; --i) {
        representation[i] = number & 1;
        number = number >> 1;
    }
} 

int decimalRepresentation(unsigned int numberDigits, short *binary) {
    int sum = 0;
    int current = 1;

    for (int i = numberDigits - 1; i > 0; --i) {
        sum += binary[i] * current;
        current <<= 1;
    }

    sum -= binary[0] * current;

    return sum;
}

int main() {
    setlocale(LC_ALL,"ru-RU");

    printf("Введите первое число: ");
    int first = 0;
    bool isString = scanf("%d", (&first));
    while (!isString) {
        printf("Введенное значение не является числом, произведите ввод снова: \n");
        fflush(stdin);
        isString = scanf("%d", &first);
    }
    printf("Введите второе число: ");
    int second = 0;
    isString = scanf("%d", (&second));
    while (!isString) {
        printf("Введенное значение не является числом, произведите ввод снова: \n");
        fflush(stdin);
        isString = scanf("%d", &second);
    }

    //определение количества разрядов
    unsigned int numberDigits = (unsigned int)ceil(log2(abs(first) > abs(second) ? abs(first) : abs(second))) + 1;
    //для предотвращение превращения положительных чисел в отрицательные
    if (abs(first + second) >= (pow(2, numberDigits - 1))) {
        ++numberDigits;
    }

    short* firstBinary = (short*)(calloc(numberDigits, sizeof(short)));
    if (firstBinary == NULL) {
        printf("Недостаточно памяти");
        return 1;
    }
    binaryRepresentation(first, numberDigits, firstBinary);
    printf("Двоичное представление в дополнительном коде первого числа: ");
    printArray(firstBinary, numberDigits);

    short* secondBinary = (short*)(calloc(numberDigits, sizeof(short)));
    if (secondBinary == NULL) {
        printf("Недостаточно памяти");
        return 1;
    }
    binaryRepresentation(second, numberDigits, secondBinary);
    printf("Двоичное представление в дополнительном коде второго числа: ");
    printArray(secondBinary, numberDigits);

    short *sum = columnAddition(firstBinary, secondBinary, numberDigits);
    if (sum == NULL) {
        printf("Недостаточно памяти");
        return 1;
    }

    free(firstBinary);
    free(secondBinary);

    printf("Сумма в двоичном представлении: ");
    printArray(sum, numberDigits);

    decimalRepresentation(numberDigits, sum);
    printf("Сумма в десятичном представлении: %d", decimalRepresentation(numberDigits, sum));

    free(sum);

    return 0;
}