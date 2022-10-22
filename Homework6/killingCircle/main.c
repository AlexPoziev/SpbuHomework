#include <stdio.h>
#include "list.h"

int main() {

    List *check = createList();
    int errorCode = 0;
    int *lol = &errorCode;
    int *chec = lol;

    insert(check, 0, 0);
    insert(check, 0, 0);
    insert(check, 0, 0);
    clear(&check);
    if (check == NULL) {
        printf("ewkere");
    }
    print(check);x

    return 0;
}
