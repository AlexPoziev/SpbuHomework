#pragma once

// return number of first occurrence of the substring, starting by 0
// return -1 if no substring in the string
// errorCodes:
//  1 if not enough memory
//  0 if all is ok
// -1 if no string or substring array
int findSubstring(const char *string, unsigned stringLength, char *substring, int *errorCode);

// return number of first occurrence of the substring in the file, starting by 0 and counting '\n'
// return -1 if no substring in the string
// errorCodes:
//  1 if not enough memory
//  0 if all is ok
// -1 if no substring array
// -2 if file doesn't exist
int fileFindSubstring(char *fileName, char *substring, int *errorCode);