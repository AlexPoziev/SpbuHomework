#include "statesTest.h"
#include "states.h"
#include <stdlib.h>

// tests

bool createStatesTest(void) {
    States *states = createStates();

    bool test = states != NULL;

    deleteStates(&states);

    return test;
}

bool createCitiesTest(void) {
    Cities *cities = createCities();

    bool test = cities != NULL;

    deleteCities(&cities);

    return test;
}

bool deleteStatesTest(void) {
    States *states = createStates();

    bool firstTest = states != NULL;

    deleteStates(&states);

    bool secondTest = states == NULL;

    return firstTest && secondTest;
}

bool deleteCitiesTest(void) {
    Cities *cities = createCities();

    bool firstTest = cities != NULL;

    deleteCities(&cities);

    bool secondTest = cities == NULL;

    return firstTest && secondTest;
}

bool getDataFromFileTest(void) {

}