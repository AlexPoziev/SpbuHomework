#pragma once
#include <stdio.h>
#include <stdbool.h>

#define MAX_CONTACT_SIZE 20

typedef struct PhoneBook{
    char phone[MAX_CONTACT_SIZE];
    char name[MAX_CONTACT_SIZE];
} PhoneBook;

// put contacts from file to array
// return 0 is all is ok
// return 1 if no file with that name
int getFileData(const char* fileName, PhoneBook data[], unsigned int *size);

// find phone number by name
char* findByName(PhoneBook data[], const char* name, unsigned int size);

// find name by phone number
char* findByPhoneNumber(PhoneBook data[], const char* string, unsigned int size);

// print all names and numbers
void printAllContacts(PhoneBook data[], unsigned int size);

// save all names and phone numbers to file
void saveContacts(const char *fileName, PhoneBook data[], unsigned int size);

// correct test
bool correctTests(void);
