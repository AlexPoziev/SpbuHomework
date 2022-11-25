#include "bracketsBalance.h"
#include "../stack/stack.h"
#include <stdlib.h>
#include <stdbool.h>

bool bracketsBalance(char *string, unsigned long size, int *errorCode) {
    if (size == 0) {
        return true;
    }

    IntStack *head = NULL;

    for (int i = 0; i < size; ++i) {
        if (string[i] == '{' || string[i] == '(' || string[i] == '[') {
            *errorCode = pushInt(&head, string[i]);
            if (*errorCode) {
                clearIntStack(&head);
                return false;
            }
        } else {
            //get last value } ] )
            int value = popInt(&head, errorCode);
            //if stack empty and close bracket its false
            if (*errorCode == -1 || !((value == '(' && string[i] == ')')
                || (value == '[' && string[i] == ']') || (value == '{' && string[i] == '}'))) {
                clearIntStack(&head);
                return false;
            }
        }
    }

    if (isIntEmpty(head)) {
        return true;
    } else {
        clearIntStack(&head);
        return false;
    }
}

bool correctTest(void) {
    char firstCheck[6] = "()[]{}";
    char secondCheck[0] = "";
    char thirdCheck[16] = "([{}]){}{}[]{()}";
    int errorCode = 0;

    return bracketsBalance(firstCheck, 6, &errorCode)
        && bracketsBalance(secondCheck, 0, &errorCode)
        && bracketsBalance(thirdCheck, 16, &errorCode);
}

bool incorrectTest(void) {
    char firstCheck[1] = "(";
    char secondCheck[3] = "())";
    char thirdCheck[2] = "(}";
    char fourthCheck[4] = "{(})";
    int errorCode = 0;

    return !bracketsBalance(firstCheck, 1, &errorCode)
        && !bracketsBalance(secondCheck, 3, &errorCode)
        && !bracketsBalance(thirdCheck, 2, &errorCode)
        && !bracketsBalance(fourthCheck, 4, &errorCode);
}

bool bracketsBalanceTest(void) {
    return correctTest() && incorrectTest();
}