#include "commentsTest.h"
#include "comments.h"
#include <string.h>
#include <stdlib.h>

bool commentsTest(void) {
    int errorCode = 0;
    char *comment = getCommentsFromFile("firstTest.txt", &errorCode);
    bool firstTest = !strcmp(comment, "/*\n    comment\n        with\n            bad spaces */\n");

    free(comment);

    comment = getCommentsFromFile("secondTest.txt", &errorCode);
    bool secondTest = !strcmp(comment, "/*321123*/\n");

    free(comment);

    comment = getCommentsFromFile("thirdTest.txt", &errorCode);
    bool thirdTest = !strcmp(comment, "");

    free(comment);

    return firstTest && secondTest && thirdTest;
}