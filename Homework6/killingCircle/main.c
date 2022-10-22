#include <stdio.h>
#include "list.h"

int circleOfDeath(int elementsCount, int gap) {
    int errorCode = 0;
    List *list = createList();
    for (int i = 0; i < elementsCount; ++i) {
        insert(list, i, i);
    }
    print(list);
    while (listSize(list) > 1) {
        gap+=gap;
        cycleListDelete(list, gap, &errorCode);
        print(list);
    }

    return delete(list, 0, &errorCode);
}

int main() {
    int elementsCount = 5;
    int errorCode = 0;
    List *list = createList();
    for (int i = 0; i < elementsCount; ++i) {
        insert(list, i, i);
    }
    print(list);
    cycleListDelete(list, 2, &errorCode);
    print(list);
    cycleListDelete(list, 2, &errorCode);
    print(list);
    cycleListDelete(list, 7, &errorCode);
    print(list);
    printf("%d %d", listSize(list), errorCode);

    return 0;
}
