#include "list.h"
#include <stdio.h>

int main() {
    List *list = createList();

    addWord(list, "check");
    addWord(list, "check");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "checkf");
    addWord(list, "checkt");
    addWord(list, "check3");

    printList(list);
    return 0;
}
