#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double performOperation(double firstNumber, double secondNumber, char operation, int *errorCode) {
    switch (operation) {
        case '*':
        {
            return firstNumber * secondNumber;
        }
        case '-':
        {
            return secondNumber - firstNumber;
        }
        case '+':
        {
            return firstNumber + secondNumber;
        }
        case '/':
        {
            return secondNumber / firstNumber;
        }
        default:
        {
            *errorCode = -1;
            return 0;
        }
    }
}

double postfixCalculator(char *expression, unsigned expressionSize, int *errorCode) {
    Stack *head = NULL;
    *errorCode = 0;

    for (int i = 0; i < expressionSize; ++i) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            *errorCode = push(&head, expression[i] - '0');
            //check for memory in push
            if (*errorCode == 1) {
                return -1;
            }
        } else {
            double firstNumber = pop(&head, errorCode);
            if (*errorCode == -1) {
                //code 2 incorrect expression
                printf("1");
                return 0;
            }
            double secondNumber = pop(&head, errorCode);
            if (*errorCode == -1) {
                return 0;
            }
            firstNumber = performOperation(firstNumber, secondNumber, expression[i], errorCode);
            if (*errorCode == -1) {
                return 0;
            }
            push(&head, firstNumber);
        }
    }
    double sum = pop(&head, errorCode);
    //check that its only number in stack
    if (isEmpty(head)) {
        return sum;
    } else {
        clearStack(&head);
        *errorCode = -1;
        return 0;
    }
}

int main() {
    char *test = "+";
    int errorCode = 0;
    double check = postfixCalculator(test, 8, &errorCode);
    if (errorCode == -1) {
        printf("incorrect expression");
    }
    if (errorCode == 1) {
        printf("Not enough memory");
    }
    return 0;
}
