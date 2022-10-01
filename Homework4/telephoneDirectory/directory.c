#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char phone[10];
    char *name;
}PhoneBook;

int main() {
    FILE *file = fopen("telephoneNumbers.txt", "r");
    if (file == NULL) {
        file = fopen("telephoneNumbers.txt", "w");
    }
    fclose(file);

    printf(" 0 - exit \n 1 - add contact \n 2 - print all contacts \n 3 - print phone number by name \n 4 - print name by phone number \n 5 - save all current data \n");
    
    int choice = -1;
    while (choice != 0) {
        printf("Choose option 0 - 5: ");
        scanf("%d", &choice);
        while (choice > 5 && choice < 0) {

        }

        switch (choice) {
            case 1:
            {
                PhoneBook entry;
                entry.name = (char*)(calloc(30, sizeof(char)));
                file = fopen("telephoneNumbers.txt", "r");
                fscanf(file, "%s", entry.name);
                fscanf(file, "%[^\n]", entry.phone);

                printf("%s %s \n", entry.name, entry.phone);

                fclose(file);
                free(entry.name);
                continue;
            }
            case 2:
            {
                printf("2");
                continue;
            }
            case 3:
            {

                continue;
            }
            case 4:
            {

                continue;
            }
            case 5:
            {

                continue;
            }

        }
    }

    return 0;
}
