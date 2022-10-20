#include "phone.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct PhoneBook{
    char *phone;
    char *name;
}PhoneBook;

bool correctTests(void) {
    const char *testFile = "test.txt";
    FILE *file = fopen(testFile, "w");
    fclose(file);

    char* data[3] = {"Tarantino 8999133777", "Paradox 014-554-3", "Kel'Thas +7 (918) 147-14-70"};
    saveContacts(file, data, 3,testFile);
    char firstCheck[10] = {0};
    char secondCheck[7] = {0};
    char thirdCheck[18] = {0};

    // test to find by name/phone number
    findByString(file, testFile, "Tarantino", firstCheck);
    findByString(file, testFile, "014-554-3", secondCheck);
    findByString(file, testFile, "Kel'Thas", thirdCheck);

    char firstInputCheck[10] = {0};
    char secondInputCheck[10] = {0};
    file = fopen(testFile, "r");
    fscanf(file, "%s", firstInputCheck);
    fgetc(file);
    fscanf(file, "%[^\n]", secondInputCheck);
    fclose(file);

    return !strcmp(firstCheck, "8999133777") && !strcmp(secondCheck, "Paradox") && !strcmp(thirdCheck, "+7 (918) 147-14-70") && !strcmp(firstInputCheck, "Tarantino") && !strcmp(secondInputCheck, "8999133777");
}

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

    printf(" 0 - exit \n 1 - add contact \n 2 - print all contacts \n 3 - print phone number by name \n 4 - print name by phone number \n 5 - save all current data \n");

    // create array with size of max contact number
    char *data[100] = {0};
    // variable to check any changes in file
    int inputUse = 0;
    int choice = -1;

    while (choice != 0) {
        printf("Choose option 0 - 5: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                data[inputUse] = (char*)(calloc(maxContactSize * 2, sizeof(char)));
                printf("Input name and phone number, separated by space: ");
                fflush(stdin);
                scanf("%[^\n]", data[inputUse]);
                ++inputUse;
                continue;
            }
            case 2: {
                printf("All contacts: \n");
                printAllContacts(file, mainFile);
                continue;
            }
            case 3: {
                PhoneBook number;

                printf("Input name with length below 15 to find name: ");
                number.phone = (char*)(calloc(maxContactSize, sizeof(char)));
                if (number.phone == NULL) {
                    printf("Not enough memory for program work");
                    return 1;
                }
                number.name = (char*)(calloc(maxContactSize, sizeof(char)));
                if (number.name == NULL) {
                    printf("Not enough memory for program work\n");
                    return 1;
                }
                scanf("%s", number.name);
                int check = findByString(file, mainFile, number.name, number.phone);
                if (check == 1) {
                    printf("Not enough memory to find\n");
                } else if (check == 2) {
                    printf("No same name in the phone directory\n");
                } else {
                    printf("phone number: %s \n", number.phone);
                }

                free(number.phone);
                free(number.name);

                continue;
            }
            case 4: {
                PhoneBook number;

                printf("Input phone number with length below 15 to find name: ");
                number.phone = (char*)(calloc(maxContactSize, sizeof(char)));
                if (number.phone == NULL) {
                    printf("Not enough memory for program work");
                    return 1;
                }
                number.name = (char*)(calloc(maxContactSize, sizeof(char)));
                if (number.name == NULL) {
                    printf("Not enough memory for program work");
                    return 1;
                }
                fflush(stdin);
                scanf("%[^\n]", number.phone);
                int check = findByString(file, mainFile, number.phone, number.name);
                if (check == 1) {
                    printf("Not enough memory to find \n");
                } else if (check == 2) {
                    printf("No same number in the phone directory \n");
                } else {
                    printf("name: %s \n", number.name);
                }

                free(number.phone);
                free(number.name);

                continue;
            }
            case 5: {
                if (!inputUse) {
                    printf("Nothing to save\n");
                } else {
                    saveContacts(file, data, inputUse,mainFile);
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
    for (int i = 0; i < 100; ++i) {
        free(data[i]);
    }

    return 0;
}
