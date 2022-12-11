#include "lexer.h"

typedef enum State {
    start,
    startDigit,
    point,
    pointDigit,
    exponent,
    exponentSign,
    exponentDigit
} State;

bool isDigit(char symbol) {
    return symbol >= '0' && symbol <= '9';
}

bool isRealNumber(const char *expression) {
    State currentState = start;
    unsigned int currentPosition = 0;

    while (expression[currentPosition] != '\0') {
        char currentSymbol = expression[currentPosition];
        ++currentPosition;

        // stupid warning
        switch (currentState) {
            case start: {
                if (!isDigit(currentSymbol)) {
                    return false;
                }

                currentState = startDigit;

                break;
            }

            case startDigit: {
                if (isDigit(currentSymbol)) {
                    break;
                }
                if (currentSymbol == '.') {
                    currentState = point;
                    break;
                }
                if (currentSymbol == 'e' || currentSymbol == 'E') {
                    currentState = exponent;
                    break;
                }

                return false;
            }

            case point: {
                if (isDigit(currentSymbol)) {
                    currentState = pointDigit;
                    break;
                }

                return false;
            }

            case pointDigit: {
                if (isDigit(currentSymbol)) {
                    break;
                }
                if (currentSymbol == 'e' || currentSymbol == 'E') {
                    currentState = exponent;
                    break;
                }

                return false;
            }

            case exponent: {
                if (isDigit(currentSymbol)) {
                    currentState = exponentDigit;
                    break;
                }
                if (currentSymbol == '-' || currentSymbol == '+') {
                    currentState = exponentSign;
                    break;
                }

                return false;
            }

            case exponentSign: {
                if (isDigit(currentSymbol)) {
                    currentState = exponentDigit;
                    break;
                }

                return false;
            }

            case exponentDigit: {
                if (isDigit(currentSymbol)) {
                    break;
                }

                return false;
            }
        }
    }

    return currentState == startDigit || currentState == pointDigit || currentState == exponentDigit;
}