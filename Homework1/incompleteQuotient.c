#include <stdio.h>
#include <stdbool.h>

int incompleteQuotient(int dividend, int divisor) { //рассмотрим два случая: 1)(++, +-) 2)(-+, --), так как ответ различается на знак
    int quotient = 0;
    bool isNegative = false;
    
    if (dividend == 0) {
        return 0;
    }
    if (divisor < 0) {
        isNegative = true;
        divisor *= -1;
    }
    
    if (dividend > 0) { //проверка к какой паре относится
        while (dividend >= divisor) {
            dividend -= divisor;
            ++quotient;
        }
        if (isNegative == true) {
            return -quotient;
        } else {
            return quotient;
        }
    } else {
        while (dividend < 0) {
            dividend += divisor;
            ++quotient;
        }
        if (isNegative == true) {
            return quotient;
        } else { 
            return -quotient;
        }
    }
}

int main() {
    int firstNumber = 0;
    int secondNumber = 0;

    printf("Для получения неполного частного введите делимое и делитель через пробел: ");
    scanf("%d %d", &firstNumber, &secondNumber);

    if (secondNumber == 0) {
        printf("Значение деления на 0 не определено");
    } else {
        printf("Вывод: %d", incompleteQuotient(firstNumber, secondNumber));
    }

    return 0;
}