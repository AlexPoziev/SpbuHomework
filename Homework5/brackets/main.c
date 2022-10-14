#include "stack.h"
#include <stdio.h>
#include <string.h>

bool bracketsBalance(char *string, unsigned long size) {
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

int main() {
    if (!correctTest() || !incorrectTest()) {
        printf("Tests failed");
        return 1;
    }

    char string[1000];

    printf("Input a string of brackets balance with length below 1000: ");
    fgets(string, sizeof string, stdin);
    printf("Balance of brackets: %s", (bracketsBalance(string, strlen(string) - 1)) ? "correct" : "incorrect");
    return 0;
}
