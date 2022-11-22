#include "states.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct States {
    List **states;
    unsigned int statesCount;
} States;

typedef struct Cities {
    unsigned int **roads;
    unsigned int citiesCount;
} Cities;

void freeMatrix(unsigned int **matrix, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        free(matrix[i]);
    }

    free(matrix);
    matrix = NULL;
}

unsigned int** createMatrix(unsigned int size) {
    unsigned int **matrix = calloc(size, sizeof(unsigned int*));
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

void printMatrix(unsigned int **matrix, unsigned int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%u ", matrix[i][j]);
        }
        printf("\n");
    }
}

States* createStates(void) {
    return malloc(sizeof(States));
}

Cities* createCities(void) {
    return malloc(sizeof(Cities));
}

// delete states and clear memory
void deleteStates(States **states) {
    if (states == NULL || *states == NULL) {
        return;
    }
    for (int i = 0; i < (*states)->statesCount; ++i) {
        deleteList(&((*states)->states[i]));
    }

    free(*states);
    *states = NULL;
}

// delete road and clear memory
void deleteCities(Cities **roads) {
    if (roads == NULL || *roads == NULL) {
        return;
    }
    freeMatrix((*roads)->roads, (*roads)->citiesCount);

    free(*roads);
    *roads = NULL;
}

// return -1 if no file with fileName
// return 0 if all is ok
// return 1 if not enough memory
int getDataFromFile(char *fileName, Cities *cities, States *states) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return -1;
    }

    unsigned int roadsNumber = 0;

    // number of cities and roads
    int eofCheck = fscanf(file, "%u %u", &cities->citiesCount, &roadsNumber);
    if (eofCheck == EOF) {
        fclose(file);
    }

    cities->roads = createMatrix(cities->citiesCount);
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

            return 2;
        }

        cities->roads[firstCity - 1][secondCity - 1] = roadLength;
    }

    eofCheck = fscanf(file, "%u", &states->statesCount);
    if (eofCheck == EOF) {
        fclose(file);

        return 2;
    }

    states->states = calloc(states->statesCount, sizeof(List*));
    if (states->states == NULL) {
        fclose(file);
        return 1;
    }

    for (int i = 0; i < states->statesCount; ++i) {
        unsigned int capital = 0;
        eofCheck = fscanf(file, "%u", &capital);
        if (eofCheck == EOF) {
            fclose(file);
            return 2;
        }

        states->states[i] = createList();
        if (states->states[i] == NULL) {
            fclose(file);
            return 1;
        }

        int errorCode = addValue(states->states[i], capital - 1);
        if (errorCode == 1) {
            fclose(file);
            return 1;
        }
    }

    printMatrix(cities->roads, cities->citiesCount);
    for (int i = 0; i < states->statesCount; ++i) {
        printList(states->states[i]);
    }

    fclose(file);

    return 0;
}

// if city in state zero its column
void zeroColumn(Cities *cities, unsigned int columnNumber) {
    for (int i = 0; i < cities->citiesCount; ++i) {
        cities->roads[i][columnNumber] = 0;
    }
}

int divideCities(Cities *cities, States *states) {
    int errorCode = 0;
    // zero capitals columns
    for (int i = 0; i < states->statesCount; ++i) {
        unsigned int city = getListElementValue(getFirstListElement(states->states[i]), &errorCode);
        zeroColumn(cities, city);
    }

    // how many free cities left
    unsigned int citiesLeft = cities->citiesCount - states->statesCount;

    while (citiesLeft != 0) {
        for (int i = 0; i < states->statesCount; ++i) {
            int minLength = UINT32_MAX;

        }
    }
}