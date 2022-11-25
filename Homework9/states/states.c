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

// idea:
// create matrix of roads to cities and states lists
// matrix: if exists road to city it contains length of it, else - 0
// if some city contains in state - zero column to this city
// going through all states and find min way to not stated city
// add it to state list
// check for case if no roads to city exists
// print all states

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
void deleteCities(Cities **cities) {
    if (cities == NULL || *cities == NULL) {
        return;
    }
    freeMatrix((*cities)->roads, (*cities)->citiesCount);

    free(*cities);
    *cities = NULL;
}

// return -1 if no file with fileName
// return 0 if all is ok
// return 1 if not enough memory
// return 2 if not enough data in test file
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

        if (firstCity > cities->citiesCount || secondCity > cities->citiesCount) {
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

    if (states->statesCount > cities->citiesCount) {
        fclose(file) ;
        return -3;

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

        if (capital > cities->citiesCount) {
            fclose(file);
            return -2;
        }

        eofCheck = fgetc(file);
        if (eofCheck == EOF && i != states->statesCount - 1) {
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

    fclose(file);

    return 0;
}

// if city in state zero its column
void zeroColumn(Cities *cities, unsigned int columnNumber) {
    for (unsigned int i = 0; i < cities->citiesCount; ++i) {
        cities->roads[i][columnNumber] = 0;
    }
}

void getMinInLine(Cities *cities, unsigned value, unsigned *minLength, unsigned *minCityNumber) {
    for (unsigned int i = 0; i < cities->citiesCount; ++i) {
        if (cities->roads[value][i] != 0 && cities->roads[value][i] < *minLength) {
            *minLength = cities->roads[value][i];
            *minCityNumber = i;
        }
    }
}

int divideCities(Cities *cities, States *states) {
    int errorCode = 0;
    // zero capitals columns
    for (unsigned int i = 0; i < states->statesCount; ++i) {
        unsigned int city = getListElementValue(getFirstListElement(states->states[i]), &errorCode);
        zeroColumn(cities, city);
    }

    // how many free cities left
    unsigned int citiesLeft = cities->citiesCount - states->statesCount;

    while (citiesLeft != 0) {
        // check for case if no way to city
        bool wasAction = false;
        for (unsigned int i = 0; i < states->statesCount; ++i) {
            unsigned int minLength = UINT32_MAX;
            unsigned int minCityNumber = UINT32_MAX;

            ListElement *element = getFirstListElement(states->states[i]);

            while (element != NULL) {
                unsigned int value = getListElementValue(element, &errorCode);
                getMinInLine(cities, value, &minLength, &minCityNumber);
                element = getNextElement(element);
            }

            if (minLength != UINT32_MAX) {
                wasAction = true;
                errorCode = addValue(states->states[i], minCityNumber);
                if (errorCode == 1) {
                    return 1;
                }

                --citiesLeft;
                zeroColumn(cities, minCityNumber);
            }
        }

        if (!wasAction) {
            return -1;
        }
    }

    return 0;
}

unsigned int getRoadLength(Cities *cities, unsigned int firstCity, unsigned int secondCity) {
    if (firstCity > cities->citiesCount || secondCity > cities->citiesCount ||
        firstCity < cities->citiesCount || secondCity < cities->citiesCount) {
        return 0;
    }

    return cities->roads[firstCity][secondCity];
}

void printStates(States *states) {
    if (states == NULL || states->states == NULL) {
        return;
    }

    int errorCode = 0;

    for (int i = 0; i < states->statesCount; ++i) {
        printf("State %u contains cities: ", i + 1);

        ListElement *element = getFirstListElement(states->states[i]);

        while (element != NULL) {
            printf("%u ", getListElementValue(element, &errorCode) + 1);
            element = getNextElement(element);
        }

        printf("\n");
    }
}