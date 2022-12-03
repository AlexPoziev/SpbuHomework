#include "substring.h"
#include "substringTest.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Not enough data");
        return 0;
    }

    if (argc == 3 && !strcmp("--test", argv[2])) {
        if (!substringTest()) {
            printf("Tests Failed");
            return 1;
        }

        printf("Tests Passed");
        return 0;
    }

    printf("Input substring, with length less than 1000: ");
    char substring[1000] = {0};
    scanf("%s", substring);

    int errorCode = 0;
    int position = findSubstring(argv[1], substring, &errorCode);
    if (errorCode == 1) {
        printf("Not enough memory") ;
        return 1;
    }

    printf("Position of the first occurrence: %d", position);

    return 0;
}
