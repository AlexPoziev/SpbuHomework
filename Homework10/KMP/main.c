#include "substring.h"
#include "substringTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned getTotalSentenceLength(int argc, char **argv) {
    unsigned length = 0;
    for (int i = 1; i < argc; ++i) {
        length += strlen(argv[i]);
        // space
        ++length;
    }

    return --length;
}

void argCat(int argc, char **argv, char *substring) {
    unsigned currentSubstringPosition = 0;

    for (int i = 1; i < argc - 1; ++i) {
        unsigned j = 0;

        while(argv[i][j] != '\0') {
            substring[currentSubstringPosition] = argv[i][j];
            ++currentSubstringPosition;
            ++j;
        }

        substring[currentSubstringPosition] = ' ';
        ++currentSubstringPosition;
    }

    unsigned j = 0;
    while(argv[argc - 1][j] != '\0') {
        substring[currentSubstringPosition] = argv[argc - 1][j];
        ++currentSubstringPosition;
        ++j;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Not enough data");
        return 0;
    }

    if (!strcmp("--test", argv[1])) {
        if (!substringTest()) {
            printf("Tests Failed");
            return 1;
        }

        printf("Tests Passed");
        return 0;
    }

    char *substring = calloc(getTotalSentenceLength(argc, argv), sizeof(char));
    if (substring == NULL) {
        printf("Not enough memory");
        return 1;
    }

    
    /*printf("Position of the first occurrence: %d", position);*/

    return 0;
}
