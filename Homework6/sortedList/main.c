#include "sortedList.h"
#include "sortedListTest.h"
#include <stdio.h>

void choose(void) {
    printf("0 - exit\n");
    printf("1 - add value to sorted list\n");
    printf("2 - delete value to sorted list\n");
    printf("3 - print list to screen\n");
}

int main() {
    if (!fullTest()) {
        printf("Tests failed");
        return 1;
    }

    List *list = createList();
    if (list == NULL) {
        printf("Not enough memory");
        return 1;
    }
    
    choose();

    int option = 1;
    while (option != 0) {
        printf("Choose option: ");
        scanf("%d", &option);
        switch (option) {
            case 0: {
                break;
            }
            case 1: {
                printf("input value: ");
                int value = 0;
                scanf("%d", &value);
                int errorCode = errorCode = insert(list, value);
                if (errorCode) {
                    printf("Not enough memory");
                    deleteList(&list);
                    return 1;
                }

                break;
            }
            case 2: {
                printf("input value, that u want to delete from list: ");
                int value = 0;
                scanf("%d", &value);
                int errorCode = delete(list, value);
                if (errorCode) {
                    printf("There is no element with value: %d \n", value);
                }

                break;
            }
            case 3: {
                printList(list);
                printf("\n");

                break;
            }
            default: {
                printf("There is no option with this number");
            }
        }
    }
    
    deleteList(&list);

    return 0;
}
