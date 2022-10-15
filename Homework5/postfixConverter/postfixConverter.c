#include "postfixConverter.h"
#include "../stack/stack.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int priorityDeterminant(char operation) {
    switch (operation) {
        case '+':
        case '-':
        {
            return 1;
        }
        case '*':
        case '/':
        {
            return 2;
        }
        case ')':
        {
            return 0;
        }
        default:
        {
            return -1;
        }
    }
}

int postfixConverter(char *expression, unsigned size) {
    char *tempString = (char*)(malloc(sizeof(char) * size));
    if (tempString == NULL) {
        return 1;
    }
    IntStack *head = (IntStack*)(malloc(sizeof(IntStack)));
    if (head == NULL) {
        return 1;
    }
    int errorCode = 0;
    unsigned postfixStep = 0;

    for (int i = 0; i < size; ++i) {
        // if number than add to string
        if ((expression[i] >= '0' && expression[i] <= '9')) {
            inputChar(tempString, &postfixStep, expression[i]);
        } else if (expression[i] == '(') {
            if (pushInt(&head, expression[i])) {
                return 1;
            }
        } else if (expression[i] == ')') {
            if (closingParentheses(tempString, &postfixStep, &head)) {
                return -1;
            }
        } else if (head == NULL) {
            if (pushInt(&head, expression[i])) {
                return 1;
            }
        } else {
            int current = priorityDeterminant(expression[i]);
            while (priorityDeterminant((char)(head->value)) >= current) {
                inputChar(tempString, &postfixStep, (char)popInt(&head, &errorCode));
            }
            if (pushInt(&head, expression[i])) {
                return 1;
            }
        }
    }
    while (head != NULL) {
        inputChar(tempString, &postfixStep, (char)popInt(&head, &errorCode));
    }
    return 0;
}

int closingParentheses(char *tempString, unsigned *postfixStep, IntStack **head) {
    int errorCode = 0;
    while (*head != NULL && (*head)->value != '(') {
        inputChar(tempString, postfixStep, (char)popInt(head, &errorCode));
    }
    if (*head == NULL) {
        return -1;
    }
    popInt(head, &errorCode);

    return 0;
}

void inputChar(char *tempString, unsigned *postfixStep, char value) {
    tempString[*postfixStep] = value;
    ++(*postfixStep);
    tempString[*postfixStep] = ' ';
    ++(*postfixStep);
}
