#include <stdio.h>
#include "list.h"
#include "mergeSort.h"

int main() {
    List *list = createList();
    FILE *file = NULL;
    const char* textName = "test.txt";
    getFromFile(file, textName, list);
    Position *middle = createPosition();
    getMiddlePosition(list, middle);
    bool check = isEnd(middle);
    list = sort(list, phoneNumber);
    printList(list);
}
