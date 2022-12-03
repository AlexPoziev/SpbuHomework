#include "substring.h"
#include <stdlib.h>
#include <string.h>

unsigned* createSubstringPostfixTable(char *substring) {
    unsigned substringLength = strlen(substring);
    unsigned *postfixTable = calloc(substringLength, sizeof(unsigned));
    if (postfixTable == NULL) {
        return NULL;
    }

    for (int i = 1; i < substringLength; ++i) {
        unsigned currentValue = postfixTable[i - 1];
        while (currentValue > 0 && substring[currentValue] != substring[i]) {
            currentValue = postfixTable[currentValue - 1];
        }

        if (substring[currentValue] == substring[i]) {
            ++currentValue;
        }

        postfixTable[i] = currentValue;
    }

    return postfixTable;
}

int findSubstring(char *string, char *substring, int *errorCode) {
    ;
}