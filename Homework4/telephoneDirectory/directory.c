#include "phone.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct PhoneBook{
    char *phone;
    char *name;
}PhoneBook;

int main() {
    const char *mainFile = "telephoneNumbers.txt";
    //check on file exist, if it doesnt, creates it
    FILE *file = fopen(mainFile, "w");
    fclose(file);

    printf(" 0 - exit \n 1 - add contact \n 2 - print all contacts \n 3 - print phone number by name \n 4 - print name by phone number \n 5 - save all current data \n");

    char *data[100] = {0};
    int inputUse = 0;

    int choice = -1;
    while (choice != 0) {
        printf("Choose option 0 - 5: ");
        scanf("%d", &choice);
        while (choice > 5 || choice < 0) {
            printf("That is not option number, repeat input: ");
            scanf("%d", &choice);
        }
        bool useCaseOne = false;
        switch (choice) {
            case 1:
            {
                data[inputUse] = (char*)(calloc(30, sizeof(char)));
                printf("Input name and phone number, separated by space: ");
                fflush(stdin);
                scanf("%[^\n]", data[inputUse]);
                ++inputUse;
                continue;
            }
            case 2:
            {
                printf("All contacts: \n");
                printAllContacts(file, mainFile);
                continue;
            }
            case 4:
            {
                PhoneBook number;

                printf("Input phone number with length below 15 to find name: ");
                number.phone = (char*)(calloc(15, sizeof(char)));
                if (number.phone == NULL) {
                    printf("Not enough memory for program work");
                }
                number.name = (char*)(calloc(15, sizeof(char)));
                if (number.name == NULL) {
                    printf("Not enough memory for program work");
                }
                fflush(stdin);
                scanf("%[^\n]", number.phone);
                int check = findByString(file, number.phone, number.name, mainFile);
                if (check == 1) {
                    printf("Not enough memory to find \n");
                } else if (check == 2){
                    printf("No same number in the phone directory \n");
                } else {
                    printf("name: %s \n", number.name);
                }

                free(number.phone);
                free(number.name);

                continue;
            }
            case 3:
            {
                PhoneBook number;

                printf("Input name with length below 15 to find name: ");
                number.phone = (char*)(calloc(15, sizeof(char)));
                if (number.phone == NULL) {
                    printf("Not enough memory for program work");
                }
                number.name = (char*)(calloc(15, sizeof(char)));
                if (number.name == NULL) {
                    printf("Not enough memory for program work");
                }
                scanf("%s", number.name);
                int check = findByString(file, number.name, number.phone, mainFile);
                if (check == 1) {
                    printf("Not enough memory to find");
                } else if (check == 2){
                    printf("No same number in the phone directory");
                } else {
                    printf("phone number: %s \n", number.phone);
                }

                free(number.phone);
                free(number.name);

                continue;
            }
            case 5:
            {
                if (!inputUse) {
                    printf("Nothing to save\n");
                } else {
                    saveContacts(file, data, inputUse,mainFile);
                }
                continue;
            }

        }
    }
    for (int i = 0; i < 100; ++i) {
        free(data[i]);
    }

    return 0;
}
