#include "sortedList.h"
#include <stdio.h>

int main() {
    List* list = createList();
    insert(list, 2);
    insert(list, 3);
    deleteList(&list);

    return 0;
}
