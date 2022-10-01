#pragma once
#include <stdio.h>

// find number/name by name/number in the file
int findByString(FILE *file, const char* fileName, char* string, char* answer);

//print all names and numbers
void printAllContacts(FILE *file, const char* fileName);

//save all names and phone numbers to file
void saveContacts(FILE *file, char* data[], int newContacts, const char* fileName);
