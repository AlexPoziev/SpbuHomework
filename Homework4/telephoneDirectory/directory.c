#include "phone.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    if (!correctTests()) {
        printf("Tests Failed");
        return 1;
    }

    const char *mainFile = "telephoneNumbers.txt";

    // check on file exist, if it doesn't, creates it
    FILE *file = fopen(mainFile, "r");
    if (file == NULL) {
        file = fopen(mainFile, "w");
    }
    fclose(file);

    printf(" 0 - exit "
           "\n 1 - add contact "
           "\n 2 - print all contacts "
           "\n 3 - print phone number by name "
           "\n 4 - print name by phone number "
           "\n 5 - save all current data \n");

    // create array with size of max contact number
    PhoneBook data[100];
    // variable to check any changes in file
    unsigned int inputUse = 0;
    int choice = -1;

    getFileData(mainFile, data, &inputUse);
    while (choice != 0) {
        printf("Choose option 0 - 5: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Input name with length less than 20: ");
                scanf("%s", data[inputUse].name);

                fflush(stdin);

                printf("Input phone number with length less than 20: ");
                scanf("%s", data[inputUse].phone);

                ++inputUse;

                continue;
            }
            case 2: {
                printf("All contacts: \n");
                printAllContacts(data, inputUse);

                continue;
            }
            case 3: {
                printf("Input name with length below 20 to find phone number: ");
                char name[MAX_CONTACT_SIZE] = {0};
                scanf("%s", name);

                char *answer = findByName(data, name, inputUse);
                if (answer == NULL) {
                    printf("No contact with this name\n");
                    continue;
                }

                printf("Name: %s \n", answer);

                continue;
            }
            case 4: {
                printf("Input phone number with length below 20 to find name: ");
                char phone[MAX_CONTACT_SIZE] = {0};
                scanf("%s", phone);

                char *answer = findByPhoneNumber(data, phone, inputUse);
                if (answer == NULL) {
                    printf("No contact with this phone number\n");
                    continue;
                }

                printf("Phone number: %s \n", answer);

                continue;
            }
            case 5: {
                if (!inputUse) {
                    printf("Nothing to save\n");
                } else {
                    saveContacts(mainFile, data, inputUse);
                    printf("Save completed \n");
                }

                continue;
            }
            default:
            {
                printf("That is not option number, repeat input \n");

                continue;
            }
        }
    }

    return 0;
}
