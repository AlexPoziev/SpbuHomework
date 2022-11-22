#include "states.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct States {
    List **states
} States;

typedef struct Cities {
    unsigned int **roads;
} Cities;

void freeMatrix(unsigned int **matrix, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        free(matrix[i]);
    }

    free(matrix);
    matrix = NULL;
}

unsigned int** createMatrix(unsigned int size) {
    unsigned int **matrix = calloc(size, sizeof(unsigned int));
    if (matrix == NULL) {
        return NULL;
    }

    for (unsigned int i = 0; i < size; ++i) {
        matrix[i] = calloc(size, sizeof(unsigned int));
        if (matrix[i] == NULL) {
            freeMatrix(matrix, i);
            return NULL;
        }
    }

    return matrix;
}

States* createStates(void) {
    return malloc(sizeof(States));
}

Cities* createCities(void) {
    return malloc(sizeof(Cities));
}

// return -1 if no file with fileName
// return 0 if all is ok
// return 1 if not enough memory
int createRoadsAndStatesFile(char *fileName, Cities *cities, States *states) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return -1;
    }

    unsigned int citiesNumber = 0;
    unsigned int roadsNumber = 0;

    // number of cities and roads
    int eofCheck = fscanf(file, "%u %u", &citiesNumber, &roadsNumber);
    if (eofCheck == EOF) {
        fclose(file);
    }

    cities->roads = createMatrix(citiesNumber);
    if (cities->roads == NULL) {
        fclose(file);
        return 1;
    }

    // get roads into the matrix
    for (int i = 0; i < roadsNumber; ++i) {
        unsigned int firstCity = 0;
        unsigned int secondCity = 0;
        unsigned int roadLength = 0;

        eofCheck = fscanf(file, "%u %u %u", &firstCity, &secondCity, &roadLength);
        if (eofCheck == EOF) {
            fclose(file);
            freeMatrix(cities->roads, citiesNumber);

            return 2;
        }

        cities->roads[firstCity][secondCity] = roadLength;
    }

    unsigned int capitalNumber = 0;
    eofCheck = fscanf(file, "%u", &capitalNumber);
    if (eofCheck == EOF) {
        fclose(file);
        freeMatrix(cities->roads, citiesNumber);

        return 2;
    }

    
}