#include <stdio.h>
#include "comments.h"

int main(int argc, char **argv) {
    printf("Input file name, with length less than 20: ");
    char fileName[20] = {0};
    scanf("%s", fileName);

    int errorCode = 0;

    char *comments = getCommentsFromFile(fileName, &errorCode);

    if (errorCode == 1) {
        printf("Not enough memory");
        return 1;
    }
    if (errorCode == -2) {
        printf("\n\nERROR: Last comment doesn't have end */");
        return 1;
    }
    if (errorCode == -1) {
        printf("\nNo file with this name");
        return 0;
    }

    printf("%s", comments);

    return 0;
}
