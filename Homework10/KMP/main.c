#include "substring.h"
#include "substringTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// count of all symbols in argv
unsigned getTotalSentenceLength(int argc, char **argv) {
    unsigned length = 0;
    for (int i = 1; i < argc; ++i) {
        length += strlen(argv[i]);
        // space
        ++length;
    }

    return --length;
}

// concatenate argv with spaces
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

    printf("Input file name with length less than 20: ");
    char fileName[20] = {0};
    scanf("%s", fileName);

    argCat(argc, argv, substring);

    int errorCode = 0;

    int answer = fileFindSubstring(fileName, substring, &errorCode);
    if (errorCode == 1) {
        printf("Not enough memory");
        free(substring);
        return 1;
    }
    if (errorCode == -2) {
        printf("No file with this name exists");
        free(substring);
        return 0;
    }

    if (answer == -1) {
        printf("No substring in the file");
    } else {
        printf("Index of the first occurrence: %d", answer);
    }

    free(substring);

    return 0;
}
