#include "phone.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char *phone;
    char *name;
}PhoneBook;

int findByString(FILE *file, char* string, char* answer) {
    PhoneBook entry;

    file = fopen("telephoneNumbers.txt", "r");

    entry.name = calloc(30, sizeof(char));
    if (entry.name == NULL) {
        return 1;
    }
    entry.phone = calloc(15,sizeof(char));
    if (entry.phone == NULL) {
        return 1;
    }

    fscanf(file, "%s", entry.name);
    getc(file);
    fscanf(file, "%[^\n]", entry.phone);

    int checkName = strcmp(entry.name, string);
    int checkPhone = strcmp(entry.phone, string);

    while (!feof(file) && checkName && checkPhone) {
        fscanf(file, "%s", entry.name);
        getc(file);
        fscanf(file, "%[^\n]", entry.phone);
        checkName = strcmp(entry.name, string);
        checkPhone = strcmp(entry.phone, string);
    }
    if (feof(file) && checkName && checkPhone) {
        return 2;
    }

    fclose(file);

    strcpy(answer, !strcmp(entry.name, string) ? entry.phone : entry.name);

    free(entry.name);
    free(entry.phone);

    return 0;
}