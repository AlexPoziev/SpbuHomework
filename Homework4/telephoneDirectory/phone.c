#include "phone.h"
#include <string.h>
#include <stdio.h>

int getFileData(const char* fileName, PhoneBook data[], unsigned int *size) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return 1;
    }

    *size = 0;
    while (!feof(file)) {
        int eofCheck = fscanf(file, "%s", data[*size].name);
        if (eofCheck == EOF) {
            return 0;
        }
        fgetc(file);
        eofCheck = fscanf(file, "%[^\n]", data[*size].phone);
        if (eofCheck == EOF) {
            return 0;
        }

        ++(*size);
    }
    return 0;
}

// return NULL if no corresponding
// find number/name by name/number in the file
char* findByName(PhoneBook data[], const char* name, unsigned int size) {
    for (int i = 0; i < size; ++i) {
        if (!strcmp(data[i].name, name)) {
            return data[i].phone;
        }
    }

    return NULL;
}

char* findByPhoneNumber(PhoneBook data[], const char* phoneNumber, unsigned int size) {
    for (int i = 0; i < size; ++i) {
        if (!strcmp(data[i].phone, phoneNumber)) {
            return data[i].name;
        }
    }

    return NULL;
}

// print all names and numbers
void printAllContacts(PhoneBook data[], unsigned int size) {
    for (int i = 0; i < size; ++i) {
        printf("%s %s \n", data[i].name, data[i].phone);
    }
}

// print all inserted contacts to file
void saveContacts(const char *fileName, PhoneBook data[], unsigned int size) {
    FILE *file = fopen(fileName, "w");

    for (int i = 0; i < size - 1; ++i) {
        fprintf(file, "%s %s\n", data[i].name, data[i].phone);
    }

    fprintf(file, "%s %s\n", data[size - 1].name, data[size - 1].phone);

    fclose(file);
}

// tests
bool getFileDataTest(void) {
    PhoneBook data[3];
    unsigned int size = 0;
    getFileData("test.txt", data, &size);

    bool firstTest = !strcmp("Tarantino", data[0].name);
    bool secondTest = !strcmp("8999133777", data[0].phone);
    bool thirdTest = !strcmp("Kel'Thas", data[2].name);
    bool fourthTest = !strcmp("+7 (918) 147-14-70", data[2].phone);

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool findByStringTest(void) {
    PhoneBook data[10];
    unsigned int size = 1;
    getFileData("test.txt", data, &size);

    bool firstTest = !strcmp("014-554-3", findByName(data, "Paradox", size));
    bool secondTest = !strcmp("Paradox", findByPhoneNumber(data, "014-554-3", size));

    return firstTest && secondTest;
}

bool saveContactsTest(void) {
    PhoneBook data[2];
    unsigned int size = 2;
    strcpy(data[0].name, "testFirst");
    strcpy(data[0].phone, "1");
    strcpy(data[1].name, "testSecond");
    strcpy(data[1].phone, "2");

    saveContacts("saveTest.txt", data, size);
    FILE *file = fopen("saveTest.txt", "r");

    fscanf(file, "%s", data[0].name);
    bool firstTest = !strcmp(data[0].name, "testFirst");
    fgetc(file);
    fscanf(file, "%[^\n]", data[0].name);
    bool secondTest = !strcmp(data[0].name, "1");
    fscanf(file, "%s", data[0].name);
    bool thirdTest = !strcmp(data[0].name, "testSecond");
    fgetc(file);
    fscanf(file, "%[^\n]", data[0].name);
    bool fourthTest = !strcmp(data[0].name, "2");

    fclose(file);

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool correctTests(void) {
    return getFileDataTest() && findByStringTest() && saveContactsTest();
}
