#include "../stack/stackTest.h"
#include "bracketsBalance.h"
#include <stdio.h>
#include <string.h>

int main() {
    if (!correctTest() || !incorrectTest()) {
        printf("Tests failed");
        return 1;
    }

    char string[1000] = {0};

    printf("Input a string of brackets balance with length below 1000: ");
    fgets(string, sizeof string, stdin);
    printf("Balance of brackets: %s", (bracketsBalance(string, strlen(string) - 1)) ? "correct" : "incorrect");

    return 0;
}
