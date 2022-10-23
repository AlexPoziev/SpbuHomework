#include <stdio.h>
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

void columnAddition(const short *first, const short *second, unsigned numberDigits, short* sum) {
    bool anyRemainder = false;

    for (int i = (int)numberDigits - 1; i >= 0; --i) {
        sum[i] = (short)((first[i] ^ second[i]) ^ anyRemainder);
        anyRemainder = (first[i] + second[i] + anyRemainder) > 1 ? true : false;
    }
}

void binaryRepresentation(int number, unsigned int numberDigits, short* representation) {
    number = number > 0 ? number : (int)pow(2, numberDigits) + number;

    for (int i = (int)numberDigits - 1; i >= 0; --i) {
        representation[i] = (short)(number & 1);
        number = number >> 1;
    }
}

int decimalRepresentation(unsigned int numberDigits, const short *binary) {
    int sum = 0;
    int current = 1;

    for (int i = (int)numberDigits - 1; i > 0; --i) {
        sum += binary[i] * current;
        current <<= 1;
    }

    sum -= binary[0] * current;

    return sum;
}

bool compareTest(const short *first, const short *second, unsigned size) {
    for (int i = 0; i < size; ++i) {
        if (first[i] != second[i]) {
            return false;
        }
    }

    return true;
}

bool correctTest(void) {
    int first = 10;
    int second = -50;
    int third = 6;

    short checkFirst[6] = {0};
    short oneCheckFirst[6] = {0};
    short checkSecond[7] = {0};
    short oneCheckSecond[7] = {0};
    binaryRepresentation(first, 6, checkFirst);
    binaryRepresentation(first, 7, checkSecond);
    binaryRepresentation(third, 6, oneCheckFirst);
    binaryRepresentation(second, 7, oneCheckSecond);


    short correctCheckFirst[6] = {0, 0, 1, 0, 1, 0};
    short correctOneCheckFirst[6] = {0, 0, 0, 1, 1, 0};
    short correctOneCheckSecond[7] = {1, 0, 0, 1, 1, 1, 0};
    short correctCheckSecond[7] = {0, 0, 0, 1, 0, 1, 0};

    short correctFirstAddition[6] = {0, 1, 0, 0, 0, 0};
    short correctSecondAddition[7] = {1, 0, 1, 1, 0, 0, 0};

    short checkAdditionFirst[6] = {0};
    short checkAdditionSecond[7] = {0};

    columnAddition(correctCheckFirst, correctOneCheckFirst, 6, checkAdditionFirst);
    columnAddition(correctCheckSecond, correctOneCheckSecond, 7, checkAdditionSecond);

    return (compareTest(checkFirst, correctCheckFirst, 6) && compareTest(checkSecond, correctCheckSecond, 7)
    && compareTest(correctOneCheckFirst, oneCheckFirst, 6) && compareTest(correctOneCheckSecond, oneCheckSecond, 7)
    && compareTest(correctFirstAddition, checkAdditionFirst, 6) && compareTest(checkAdditionSecond, correctSecondAddition, 7)
    && decimalRepresentation(7, correctOneCheckSecond) == -50 && decimalRepresentation(6, correctFirstAddition) == 16);
}

int main() {
    setlocale(LC_ALL,"ru-RU");

    if (!correctTest()) {
        printf("Тесты провалены");
        return 1;
    }

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

    // определение количества разрядов
    unsigned int numberDigits = (unsigned int)ceil(log2(abs(first) > abs(second) ? abs(first) : abs(second))) + 1;
    // для предотвращения превращения положительных чисел в отрицательные
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

    short *sum = (short*)(calloc(numberDigits, sizeof(short)));
    if (sum == NULL) {
        printf("Недостаточно памяти");
        return 1;
    }
    columnAddition(firstBinary, secondBinary, numberDigits, sum);

    free(firstBinary);
    free(secondBinary);

    printf("Сумма в двоичном представлении: ");
    printArray(sum, numberDigits);

    decimalRepresentation(numberDigits, sum);
    printf("Сумма в десятичном представлении: %d", decimalRepresentation(numberDigits, sum));

    free(sum);

    return 0;
}