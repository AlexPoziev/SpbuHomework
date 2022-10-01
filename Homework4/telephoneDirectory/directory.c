#include "phone.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXPHONE = 15

typedef struct {
    char *phone;
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
                char *check = (char*)(calloc(10,sizeof(char)));
                if (findByString(file, "ekerre", check) == 1) {
                    printf("No same number in the file \n");
                } else {
                    printf("%s \n", check);
                }
                continue;
            }
            case 2:
            {
                printf("All contacts: \n");
                printAllContacts(file);
                continue;
            }
            case 3:
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
                scanf("%s", number.phone);
                int check = findByString(file, number.phone, number.name);
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
            case 4:
            {
                file = fopen("telephoneNumbers.txt", "r");
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
                scanf("%s", number.name);
                int check = findByString(file, number.name, number.phone);
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

                continue;
            }

        }
    }

    return 0;
}
