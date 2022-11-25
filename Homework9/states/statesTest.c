#include "statesTest.h"
#include "states.h"
#include <stdlib.h>

// tests

bool createStatesTest(void) {
    States *states = createStates();
    if (states == NULL) {
        return false;
    }

    bool test = states != NULL;

    deleteStates(&states);

    return test;
}

bool createCitiesTest(void) {
    Cities *cities = createCities();
    if (cities == NULL) {
        return false;
    }

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
    if (cities == NULL) {
        return false;
    }

    States *states = createStates();
    if (states == NULL) {
        deleteCities(&cities);
        return false;
    }

    bool firstTest = cities != NULL;

    deleteCities(&cities);

    bool secondTest = cities == NULL;

    return firstTest && secondTest;
}

bool getDataFromFileAndGetRoadLengthTest(void) {
    Cities *cities = createCities();
    if (cities == NULL) {
        return false;
    }

    States *states = createStates();
    if (states == NULL) {
        deleteCities(&cities);
        return false;
    }

    int errorCode = getDataFromFile("firstTest.txt", cities, states);
    if (errorCode) {
        deleteCities(&cities);
        deleteStates(&states);
        return false;
    }

    bool firstTest = getRoadLength(cities, 1, 2) == 2;
    bool secondTest = getRoadLength(cities, 1, 3) == 3;
    bool thirdTest = getRoadLength(cities, 2, 5) == 4;
    bool fourthTest = getRoadLength(cities, 2, 6) == 5;
    bool fifthTest = getRoadLength(cities, 3, 4) == 6;
    bool sixthTest = getRoadLength(cities, 4, 1) == 7;
    bool seventhTest = getRoadLength(cities, 5, 2) == 8;
    bool eighthTest = getRoadLength(cities, 3, 1) == 9;
    bool ninthTest = getStateCityNumber(states, 1, 1) == 1;
    bool tenthTest = getStateCityNumber(states, 2, 1) == 2;

    deleteCities(&cities);
    deleteStates(&states);

    return firstTest && secondTest && thirdTest && fourthTest && fifthTest
        && sixthTest && seventhTest && eighthTest && ninthTest && tenthTest;
}

bool divideCitiesAndGetStateCityNumberTest(void) {
    Cities *cities = createCities();
    if (cities == NULL) {
        return false;
    }

    States *states = createStates();
    if (states == NULL) {
        deleteCities(&cities);
        return false;
    }

    int errorCode = getDataFromFile("firstTest.txt", cities, states);
    if (errorCode) {
        deleteCities(&cities);
        deleteStates(&states);
        return false;
    }

    divideCities(cities, states);

    bool firstTest = getStateCityNumber(states, 1, 1) == 4;
    bool secondTest = getStateCityNumber(states, 1, 2) == 3;
    bool thirdTest = getStateCityNumber(states, 1, 3) == 1;
    bool fourthTest = getStateCityNumber(states, 2, 1) == 6;
    bool fifthTest = getStateCityNumber(states, 2, 2) == 5;
    bool sixthTest = getStateCityNumber(states, 2, 3) == 2;

    deleteCities(&cities);
    deleteStates(&states);

    return firstTest && secondTest && thirdTest
        && fourthTest && fifthTest && sixthTest;
}

bool statesTest(void) {
    return getDataFromFileAndGetRoadLengthTest() && createCitiesTest() && createStatesTest()
        && deleteCitiesTest() && deleteStatesTest() && divideCitiesAndGetStateCityNumberTest();
}