#include <stdio.h>
#include "list.h"


int main() {
    List *check = createList();
    int errorCode = 0;

    insert(check, 0, 0);
    print(check);
    insert(check, 1, 0);
    print(check);
    insert(check, 2, 0);
    print(check);
    insert(check, 3, 1);

    return 0;
}
