#include "postfixConverter.h"
#include "../stack/stack.h"

int priorityDeterminant(char operation) {
    switch (operation) {
        case '+':
        case '-':
        {
            return 0;
        }
        case '*':
        case '/':
        {
            return 1;
        }
        default:
        {
            return -1;
        }
    }
}
