#include "postfixConverter.h"
#include <stdio.h>

int main() {
    char test[100] = "(1 + 2) * (3 + 4)";
    postfixConverter(test, 17);
    printf("%s", test);
    return 0;
}
