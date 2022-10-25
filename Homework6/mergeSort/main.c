#include <stdio.h>
#include "list.h"

int main() {
    List *list = createList();
    FILE *file = NULL;
    const char* textName = "test.txt";
    getFromFile(file, textName, list);
    Position *check = createPosition();
    getMiddlePosition(list, check);
    printList(list);
}
