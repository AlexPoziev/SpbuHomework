#include "../stack/stackTest.h"
#include "postfixConverter.h"
#include <stdio.h>
#include <string.h>


int main() {
    if (!correctTest() || !stackTest()) {
        printf("Tests Failed");
        return 1;
    }

    char expression[1000] = {0};

    printf("Input postfix expression with length below 1000: ");
    fgets(expression, sizeof(expression), stdin);
    int errorCode = postfixConverter(expression, strlen(expression) - 1);

    if (errorCode == -1) {
        printf("Incorrect expression");
        return 0;
    }

    if (errorCode == 1) {
        printf("Not enough memory");
        return 1;
    }

    printf("Postfix expression: %s", expression);

    return 0;
}
