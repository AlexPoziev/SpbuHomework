#include <stdio.h>
#include "list.h"

int main() {
    List *check = createList();
    int errorCode = 0;
    insert(check, 0, 9);
    delete(check, 0, &errorCode);

    return 0;
}
