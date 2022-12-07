#include <stdio.h>
#include "comments.h"

int main() {
    int errorCode = 0;
    unsigned **check = getDFATable("test.txt", &errorCode);

    return 0;
}
