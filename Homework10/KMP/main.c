#include <stdio.h>
#include "substring.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Not enough data");
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
