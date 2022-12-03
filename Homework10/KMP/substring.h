#pragma once

// return number of first occurrence of the substring, starting by 0
// return -1 if no substring in the string
// errorCodes:
//  1 if not enough memory
//  0 if all is ok
// -1 if no string or substring array
int findSubstring(char *string, char *substring, int *errorCode);
