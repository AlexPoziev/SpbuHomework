#include "stack.h"
#include <stdio.h>
#include <string.h>

bool bracketsBalance(char *string, int size) {
    if (size == 0) {
        return true;
    }

    Stack *head = NULL;

    for (int i = 0; i < size; ++i) {
        if (string[i] == '{' || string[i] == '(' || string[i] == '[') {
            push(&head, string[i]);
        } else {
            int errorCode = 0;
            //get last value } ] )
            char value = pop(&head, &errorCode);
            //if stack empty and close bracket its false
            if (errorCode == -1 || !((value == '(' && string[i] == ')') || (value == '[' && string[i] == ']') || (value == '{' && string[i] == '}'))) {
                return false;
            }
        }
    }

    if (isEmpty(head)) {
        return true;
    } else {
        clearStack(&head);
        return false;
    }
}

int main() {
    char string[100];

    printf("Input a string of brackets balance: ");
    fgets(string, sizeof string, stdin);
    printf("Balance of brackets: %s \n", (bracketsBalance(string, strlen(string) - 1)) ? "correct" : "incorrect");
    return 0;
}
