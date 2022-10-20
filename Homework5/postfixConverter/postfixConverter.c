#include "postfixConverter.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int priorityDeterminant(char operation) {
    switch (operation) {
        case '+':
        case '-': {
            return 1;
        }
        case '*':
        case '/': {
            return 2;
        }
        default: {
            return -1;
        }
    }
}

int postfixConverter(char *expression, unsigned size) {
    char *tempString = (char*)(calloc(size, sizeof(char)));
    if (tempString == NULL) {
        return 1;
    }
    IntStack *head = NULL;

    int errorCode = 0;
    unsigned postfixStep = 0;

    for (int i = 0; i < size; ++i) {
        if (expression[i] == ' ') {
            continue;
        }
        // if number then add to string
        if ((expression[i] >= '0' && expression[i] <= '9')) {
            inputChar(tempString, &postfixStep, expression[i]);
        } else if (expression[i] == '(') {
            if (pushInt(&head, expression[i])) {
                free(tempString);
                clearIntStack(&head);
                return 1;
            }
        } else if (expression[i] == ')') {
            if (closingParentheses(tempString, &postfixStep, &head)) {
                free(tempString);
                clearIntStack(&head);
                return -1;
            }
        } else {
            int current = priorityDeterminant(expression[i]);
            while (head != NULL && priorityDeterminant((char)(head->value)) >= current) {
                inputChar(tempString, &postfixStep, (char)popInt(&head, &errorCode));
            }
            if (pushInt(&head, expression[i])) {
                free(tempString);
                clearIntStack(&head);
                return 1;
            }
        }
    }
    while (head != NULL) {
        inputChar(tempString, &postfixStep, (char)popInt(&head, &errorCode));
    }
    strcpy(expression, tempString);

    free(tempString);
    free(head);
    clearIntStack(&head);

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

bool correctTest(void) {
    char expressionFirst[17] = "(1 + 2) * (3 + 4)";
    char expressionSecond[17] = "1 + 2 / 3 * 5 + 3";
    char expressionThird[13] = "1 + 2 + 3 + 4";
    char expressionsFourth[6] = "1 + 2)";

    postfixConverter(expressionFirst, 17);
    postfixConverter(expressionSecond, 17);
    postfixConverter(expressionThird, 13);
    int check = postfixConverter(expressionsFourth, 6);

    return !strcmp(expressionFirst, "1 2 + 3 4 + * ") && !strcmp(expressionSecond, "1 2 3 / 5 * + 3 + ")
    && !strcmp(expressionThird, "1 2 + 3 + 4 + ") && check == -1;
}
