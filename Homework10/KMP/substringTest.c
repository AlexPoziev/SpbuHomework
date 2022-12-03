#include "substringTest.h"
#include "substring.h"

bool substringTest(void) {
    int errorCode = 0;
    bool firstTest = findSubstring("12345", "34", &errorCode) == 2;
    bool secondTest = findSubstring("12345", "35", &errorCode) == -1;
    bool thirdTest = findSubstring("abcde", "abcde", &errorCode) == 0;
    bool fourthTest = findSubstring("1234", "12345", &errorCode) == -1;

    return firstTest && secondTest && thirdTest && fourthTest;
}