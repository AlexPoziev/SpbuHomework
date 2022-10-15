#include "bracketsBalance.h"
#include "../stack/stack.h"
#include <stdlib.h>
#include <stdbool.h>

bool bracketsBalance(char *string, unsigned long size) {
    if (size == 0) {
        return true;
    }

    IntStack *head = NULL;

    for (int i = 0; i < size; ++i) {
        if (string[i] == '{' || string[i] == '(' || string[i] == '[') {
            pushInt(&head, string[i]);
        } else {
            int errorCode = 0;
            //get last value } ] )
            int value = popInt(&head, &errorCode);
            //if stack empty and close bracket its false
            if (errorCode == -1 ||
                !((value == '(' && string[i] == ')') || (value == '[' && string[i] == ']') ||
                  (value == '{' && string[i] == '}'))) {
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

    return bracketsBalance(firstCheck, 6) && bracketsBalance(secondCheck, 0) && bracketsBalance(thirdCheck, 16);
}


bool incorrectTest(void) {
    char firstCheck[1] = "(";
    char secondCheck[3] = "())";
    char thirdCheck[2] = "(}";
    char fourthCheck[4] = "{(})";

    return !bracketsBalance(firstCheck, 1) && !bracketsBalance(secondCheck, 3) && !bracketsBalance(thirdCheck, 2) && !bracketsBalance(fourthCheck, 4);
}