#include "listTest.h"
#include "states.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// return 0 if all is ok and need to continue programs work
// return not 0 if catch error, need to return 
int getDataFromFileError(int errorCode, Cities *cities, States *states) {
    switch (errorCode) {
        case 0: {
            return 0;
        }
        case -3: {
            printf("States count more than cities count");
            deleteCities(&cities);
            deleteStates(&states);
            return -1;
        }
        case -2: {
            printf("City has number more than cities count");
            deleteCities(&cities);
            deleteStates(&states);
            return -1;
        }
        case -1: {
            printf("No file with this name");
            deleteCities(&cities);
            deleteStates(&states);
            return -1;
        }
        case 1: {
            printf("Not enough memory");
            deleteCities(&cities);
            deleteStates(&states);
            return 1;
        }
        case 2: {
            printf("Not enough data in the file");
            deleteCities(&cities);
            deleteStates(&states);
            return -1;
        }
        default: {
            deleteCities(&cities);
            deleteStates(&states);
            return -1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (!listTest()) {
        printf("Tests Failed");
        return 1;
    }
    if (argc >= 2 && !strcmp(argv[1], "--test")) {
        if (!listTest()) {
            printf("Tests Failed");
            return 1;
        }

        printf("Tests Passed");

        return 0;
    }

    Cities *cities = createCities();
    if (cities == NULL) {
        printf("Not enough memory");
        return 1;
    }

    States *states = createStates();
    if (states == NULL) {
        printf("Not enough memory");
        deleteCities(&cities);

        return 1;
    }

    printf("Input file name with length less than 20 symbols: ");
    char fileName[20] = {0};
    scanf("%s", fileName);

    int errorCode = getDataFromFileError(getDataFromFile(fileName, cities, states), cities, states);
    if (errorCode != 0) {
        return errorCode;
    }

    errorCode = divideCities(cities, states);
    if (errorCode == -1) {
        printf("Some city doesn't has roads");
        deleteCities(&cities);
        deleteStates(&states);

        return 0;
    }

    printStates(states);

    deleteCities(&cities);
    deleteStates(&states);

    return 0;
}
