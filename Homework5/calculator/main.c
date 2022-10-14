#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
        if (expression[i] == ' ') {
            continue;
        }
        if (expression[i] >= '0' && expression[i] <= '9') {
            *errorCode = push(&head, expression[i] - '0');
            //check for memory in push
            if (*errorCode == 1) {
                return -1;
            }
        } else {
            double firstNumber = pop(&head, errorCode);
            //check that stack has enough numbers for completing operation
            if (*errorCode == -1) {
                //code 2 incorrect expression
                printf("1");
                return 0;
            }
            double secondNumber = pop(&head, errorCode);
            if (*errorCode == -1) {
                return 0;
            }
            //get a result of operation
            firstNumber = performOperation(firstNumber, secondNumber, expression[i], errorCode);
            if (*errorCode == -1) {
                return 0;
            }
            //push result to stack
            push(&head, firstNumber);
        }
    }

    double sum = pop(&head, errorCode);
    //check that it's only number in stack
    if (isEmpty(head)) {
        return sum;
    } else {
        //clearStack if stack has extra values
        clearStack(&head);
        *errorCode = -1;
        return 0;
    }
}

int main() {
    char expression[1000] = {0};

    printf("Input postfix expression with length below 1000: ");
    fgets(expression, sizeof(expression), stdin);
    int errorCode = 0;
    double result = postfixCalculator(expression, strlen(expression) - 1, &errorCode);
    if (errorCode == -1) {
        printf("Incorrect expression");
        return 0;
    }
    if (errorCode == 1) {
        printf("Not enough memory");
        return 1;
    }
    printf("Result of expression: %g", result);

    return 0;
}
