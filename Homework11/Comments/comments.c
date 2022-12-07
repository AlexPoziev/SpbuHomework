#include "comments.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum Symbol {
    star,
    slash,
    other
} Symbol;

unsigned int** createMatrix() {
    unsigned int **table = (unsigned**)calloc(3, sizeof(unsigned*));
    if (table == NULL) {
        return NULL;
    }

    for (int i = 0; i < 3; ++i) {
        table[i] = calloc(4, sizeof(unsigned));
        if (table[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(table[j]);
            }

            free(table);
            return NULL;
        }
    }

    return table;
}

void deleteMatrix(unsigned **table) {
    if (table == NULL) {
        return;
    }

    for (int i = 0; i < 3; ++i) {
        free(table[i]);
    }

    free(table);
}

// if user delete matrix.txt file it's his problem that it won't work
// return -1 if no file
unsigned int** getDFATable(char *fileName, int *errorCode) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        *errorCode = -1;
        return NULL;
    }

    unsigned int **table = createMatrix();
    if (table == NULL) {
        *errorCode = 1;
        fclose(file);

        return NULL;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            fscanf(file )
        }
    }
}

int printCommentsFromFile(char *fileName) {

}