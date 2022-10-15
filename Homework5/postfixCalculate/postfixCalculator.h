#pragma once

#include <stdbool.h>

// convert * / + - from char to operators
double performOperation(double firstNumber, double secondNumber, char operation, int *errorCode);

// calculate postfix expression
double postfixCalculator(char *expression, unsigned expressionSize, int *errorCode);

// correct test of postfixCalculator
bool correctTest(void);

// incorrect test of postfixCalculator
bool incorrectTest(void);