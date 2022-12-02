#include <stdio.h>
#include "list.h"
#include "mergeSort.h"
#include "listTest.h"
#include "mergeSortTest.h"

int main() {
    if (!fullTest() || !mergeSortTest()) {
        printf("Tests Failed");
        return 1;
    }

    List *list = createList();
    if (list == NULL) {
        printf("Not enough memory");
        return 1;
    }
    printf("Please enter name of .txt file, with length less than 25: ");
    char fileName[25] = {0};
    scanf("%s", fileName);

    int errorCode = getFromFile(fileName,  list);
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
        deleteList(&list, true);
        return 0;
    }

    printf("1 - name"
           "\n2 - phone number"
           "\nPlease choose sort data (if incorrect sign - sorts by name): ");
    int chose = 0;
    scanf("%d", &chose);
    Priority priority = chose == 2 ? phoneNumber : name;
    printf("Sorted list: \n");

    errorCode = 0;
    list = sort(list, priority, &errorCode);
    if (list == NULL || errorCode) {
        deleteList(&list, true);
        printf("Not enough memory");
        return 1;
    }
    printList(list);

    deleteList(&list, true);

    return 0;
}
