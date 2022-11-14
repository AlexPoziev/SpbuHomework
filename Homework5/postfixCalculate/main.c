#include "../stack/stackTest.h"
#include "postfixCalculator.h"
#include <string.h>
#include <stdio.h>

int main() {
    if (!postfixCalculatorTest() && !stackTest()) {
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
