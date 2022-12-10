#pragma once

// return array of comments
// errorCode get values:
// -1 if file doesn't exist
// 1 if not enough memory
// 0 if all is ok
// -2 if last comment doesn't have end */
char* getCommentsFromFile(char *fileName, int *errorCode);