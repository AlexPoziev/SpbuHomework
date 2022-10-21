#include <stdio.h>
#include "list.h"

int main() {
    List *check = createList();
    insert(check, 0, 0);
    insert(check, 3, 1);
    insert(check, 4, 2);
    print(check);

    return 0;
}
