#include "phone.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define mainFile = "telephoneNumbers.txt"

typedef struct {
    char *phone;
    char *name;
}PhoneBook;

// code 1 - not enough memory, code 2 - no compares
// find number/name by name/number in the file
int findByString(FILE *file, const char* fileName, char* string, char* answer) {
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


//print all names and numbers
void printAllContacts(FILE *file, const char* fileName) {
    fopen("telephoneNumbers.txt", "r");
    char *input = (char*)(calloc(15, sizeof(char)));
    while (!feof(file)) {
        fscanf(file,"%s", input);
        printf("%s ",input);
        fscanf(file, "%[^\n]", input);
        printf("%s \n", input);
    }

    free(input);
    fclose(file);
}

void saveContacts(FILE *file, char* data[], int newContacts, const char* fileName) {
    file = fopen("telephoneNumbers.txt", "a");

    for (int i = 0; i < newContacts; ++i) {
        fprintf(file, "%s \n", data[i]);
    }

    fclose(file);
}