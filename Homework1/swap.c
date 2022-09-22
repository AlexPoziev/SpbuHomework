#include <stdio.h>

void swap(int *firstNumber, int *secondNumber) { // {1}
    *firstNumber += *secondNumber;
    *secondNumber = *firstNumber - *secondNumber;
    *firstNumber -= *secondNumber;
}

int main() {
    int first = 0;
    int second = 0;

    printf("Введите два числа через пробел: ");
    scanf("%d %d", &first, &second);
    swap(&first, &second);
    printf("Вывод выполнения операции замены мест значений: %d %d", first, second);

    return 0;
}

