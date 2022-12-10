#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comments.h"
#include "commentsTest.h"

int main(int argc, char **argv) {
    if (argc > 1 && !strcmp("--test", argv[1])) {
        if (!commentsTest()) {
            printf("Tests Failed");
            return 1;
        }

        printf("Tests Passed");
        return 0;
    }

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
        return 2;
    }
    if (errorCode == -1) {
        printf("\nNo file with this name");
        return 2;
    }

    printf("Comments:\n%s", comments);

    free(comments);

    return 0;
}
