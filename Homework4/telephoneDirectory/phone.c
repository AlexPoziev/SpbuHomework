#include "phone.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char *phone;
    char *name;
}PhoneBook;

// code 1 - not enough memory, code 2 - no compares
// find number/name by name/number in the file
int findByString(FILE *file, const char* fileName, char* string, char* answer) {
    PhoneBook entry;

    file = fopen(fileName, "r");

    entry.name = calloc(maxContactSize, sizeof(char));
    if (entry.name == NULL) {
        return 1;
    }
    entry.phone = calloc(maxContactSize,sizeof(char));
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
    fopen(fileName, "r");
    char *input = (char*)(calloc(maxContactSize, sizeof(char)));
    while (!feof(file)) {
        fscanf(file,"%s", input);
        printf("%s ",input);
        fscanf(file, "%[^\n]", input);
        printf("%s \n", input);
    }

    free(input);
    fclose(file);
}

//print all inserted contacts to file
void saveContacts(FILE *file, char* data[], int newContacts, const char* fileName) {
    file = fopen(fileName, "a");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size) {
        fprintf(file, "\n");
    }

    for (int i = 0; i < newContacts - 1; ++i) {
        fprintf(file, "%s\n", data[i]);
    }
    fprintf(file, "%s", data[newContacts - 1]);

    fclose(file);
}

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