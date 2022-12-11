#include <stdio.h>
#include "lexer.h"
#include "lexerTest.h"
#include <string.h>

int main(int argc, char **argv) {
    if (argc > 1 && !strcmp("--test", argv[1])) {
        if (!lexerTest()) {
            printf("Tests Failed");
            return 1;
        }

        printf("Tests Passed");

        return 0;
    }

    printf("Input number with length less than 100, to check is it real: ");
    char number[100] = {0};
    scanf("%s", number);

    printf("%s %s real number", number, isRealNumber(number) ? "is" : "isn't");

    return 0;
}