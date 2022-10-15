#include "../stack/stackTest.h"
#include "bracketsBalance.h"
#include <stdio.h>

int main() {
    char *check = "()(";
    printf("%d", bracketsBalance(check, 3));
    return 0;
}
