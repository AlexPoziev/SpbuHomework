#include "../stack/stackTest.h"
#include "bracketsBalance.h"
#include <stdio.h>
#include <string.h>

int main() {
    if (!bracketsBalanceTest()) {
        printf("Tests failed");
        return 1;
    }

    char string[1000] = {0};

    printf("Input a string of brackets balance with length less than 1000: ");
    fgets(string, sizeof string, stdin);

    int errorCode = 0;
    bool isBalanced = bracketsBalance(string, strlen(string) - 1, &errorCode);
    if (errorCode == 1) {
        printf("Not enough memory");
        return 1;
    }
    
    printf("Balance of brackets: %s", isBalanced ? "correct" : "incorrect");

    return 0;
}
