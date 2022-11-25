#pragma once

#include "../stack/stack.h"
#include <stdbool.h>

// return priority of operation
int priorityDeterminant(char operation);

// convert infix expression into postfix
int postfixConverter(char *expression, unsigned size);

// input all operation between parentheses
int closingParentheses(char *tempString, unsigned *postfixStep, IntStack **head);

// put char to string and add space
void inputChar(char *tempString, unsigned *postfixStep, char value);

// correct tests for
bool postfixConverterTest(void);