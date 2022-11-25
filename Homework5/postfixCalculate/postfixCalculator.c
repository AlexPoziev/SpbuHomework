#include "postfixCalculator.h"
#include "../stack/stack.h"
#include <stdio.h>
#include <stdbool.h>

double performOperation(double firstNumber, double secondNumber, char operation, int *errorCode) {
    switch (operation) {
        case '*': {
            return firstNumber * secondNumber;
        }
        case '-': {
            return secondNumber - firstNumber;
        }
        case '+': {
            return firstNumber + secondNumber;
        }
        case '/': {
            return secondNumber / firstNumber;
        }
        default: {
            *errorCode = -1;
            return 0;
        }
    }
}

double postfixCalculator(char *expression, unsigned expressionSize, int *errorCode) {
    DoubleStack *head = NULL;
    *errorCode = 0;

    for (int i = 0; i < expressionSize; ++i) {
        if (expression[i] == ' ') {
            continue;
        }

        if (expression[i] >= '0' && expression[i] <= '9') {
            *errorCode = pushDouble(&head, expression[i] - '0');
            //check for memory in push
            if (*errorCode == 1) {
                clearDoubleStack(&head);
                return 1;
            }

        } else {
            double firstNumber = popDouble(&head, errorCode);
            //check that stack has enough numbers for completing operation
            if (*errorCode == -1) {
                clearDoubleStack(&head);
                //code 2 incorrect expression
                return 0;
            }

            double secondNumber = popDouble(&head, errorCode);
            if (*errorCode == -1) {
                clearDoubleStack(&head);
                return 0;
            }

            //get a result of operation
            firstNumber = performOperation(firstNumber, secondNumber, expression[i], errorCode);
            if (*errorCode == -1) {
                clearDoubleStack(&head);
                return 0;
            }
            //push result to stack
            *errorCode = pushDouble(&head, firstNumber);
            if (*errorCode == 1) {
                clearDoubleStack(&head);
                return 0;
            }
        }
    }

    double sum = popDouble(&head, errorCode);
    //check that it's only number in stack
    if (isDoubleEmpty(head)) {
        return sum;
    } else {
        //clearStack if stack has extra values
        clearDoubleStack(&head);
        *errorCode = -1;
        return 0;
    }
}

bool correctTest(void) {
    char expressionFirst[13] = "9 6 - 1 2 + *";
    char expressionSecond[13] = "4 2 / 1 3 + *";
    char expressionThird[1] = "0";
    int errorCode = 0;

    return (postfixCalculator(expressionFirst, 13, &errorCode) == 9
    && postfixCalculator(expressionSecond, 13, &errorCode) == 8
    && postfixCalculator(expressionThird, 1, &errorCode) == 0);
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

bool postfixCalculatorTest(void) {
    return correctTest() && incorrectTest();
}