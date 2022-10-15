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