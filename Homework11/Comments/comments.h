#pragma once

// return -1 if file doesn't exist
// return 1 if not enough memory
// return 0 if all is ok
// return -2 if last comment doesn't have end */
int printCommentsFromFile(char *fileName);