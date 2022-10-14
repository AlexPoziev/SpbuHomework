#include "stack.h"
#include <stdio.h>
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

bool correctTest(void) {
    char expressionFirst[13] = "9 6 - 1 2 + *";
    char expressionSecond[13] = "4 2 / 1 3 + *";
    char expressionThird[1] = "0";
    int errorCode = 0;

    return postfixCalculator(expressionFirst, 13, &errorCode) == 9 && postfixCalculator(expressionSecond, 13, &errorCode) == 8 && postfixCalculator(expressionThird, 1, &errorCode) == 0;
}

bool incorrectTest(void) {
    char expressionFirst[15] = "9 6 - 1 2 + * -";
    char expressionSecond[3] = "- +";
    char expressionThird[3] = "- 3";
    int errorCodeFirst = 0;
    int errorCodeSecond = 0;
    int errorCodeThird = 0;

    postfixCalculator(expressionFirst, 15, &errorCodeFirst);
    postfixCalculator(expressionSecond, 3, &errorCodeSecond);
    postfixCalculator(expressionThird, 3, &errorCodeThird);

    return errorCodeFirst == -1 & errorCodeSecond == -1 && errorCodeThird == -1;
}

int main() {
    if (!incorrectTest() || !correctTest()) {
        printf("Tests Failed");
        return 1;
    }

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
