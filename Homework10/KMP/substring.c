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
    if (string == NULL || substring == NULL) {
        *errorCode = -1;
        return -1;
    }

    unsigned *prefixTable = createSubstringPostfixTable(substring);
    if (prefixTable == NULL) {
        *errorCode = 1;
        return -1;
    }

    unsigned currentTablePosition = 0;
    unsigned stringLength = strlen(string);
    unsigned substringLength = strlen(substring);

    for (unsigned i = 0; i < stringLength; ++i) {
        while (currentTablePosition > 0 && substring[currentTablePosition] != string[i]) {
            currentTablePosition = prefixTable[currentTablePosition - 1];
        }

        if (substring[currentTablePosition] == string[i]) {
            ++currentTablePosition;
        }

        if (currentTablePosition == substringLength) {
            return (int)(i - substringLength + 1);
        }
    }

    return -1;
}