#include "list.h"
#include <stdio.h>

int main() {
    if (!listTest()) {
        printf("Tests Failed");

        return 1;
    }
    List *list = createList();

    addWord(list, "check");
    addWord(list, "check");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "checkf");
    addWord(list, "checkt");
    addWord(list, "check3");

    deleteList(&list);
    return 0;
}
