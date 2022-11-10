#include <stdio.h>
#include "list.h"
#include "mergeSort.h"
#include "listTest.h"

int main() {
    if (!fullTest() || mergeSortTest()) {
        printf("Test Failed");
        return 1;
    }

    List *list = createList();
    printf("Please enter name of .txt file, with length less than 25: ");
    char fileName[25] = {0};
    scanf("%s", fileName);

    FILE *file = NULL;
    int errorCode = getFromFile(file, fileName, list);
    if (errorCode == -2) {
        printf("file with this name doesn't exist");
        return 0;
    }
    if (errorCode == 1) {
        printf("Not enough memory");
        deleteList(&list, true);
        return 1;
    }
    if (errorCode == -1) {
        printf("No corresponding phone number or name in file");
        return 0;
    }

    printf("1 - name\n2 - phone number\nPlease choose sort data (if incorrect sign - sorts by name): ");
    int chose = 0;
    scanf("%d", &chose);
    Priority priority = chose == 2 ? phoneNumber : name;
    printf("Sorted list: \n");

    list = sort(list, priority);
    if (list == NULL) {
        printf("Not enough memory");
        return 1;
    }
    printList(list);

    deleteList(&list, true);

    return 0;
}
