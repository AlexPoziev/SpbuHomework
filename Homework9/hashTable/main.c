#include "list.h"
#include <stdio.h>

int main() {
    List *list = createList();

    addWord(list, "check");
    addWord(list, "check");
    return 0;
}
