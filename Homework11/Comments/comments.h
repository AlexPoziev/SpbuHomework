#pragma once

// print comments of type: /* {comment} */ from file
// return 0 if all is ok
// return 1 if not enough memory

int printCommentsFromFile(char *fileName);

unsigned int** getDFATable(char *fileName, int *errorCode);