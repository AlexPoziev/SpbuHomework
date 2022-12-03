#include "substringTest.h"
#include "substring.h"

bool findSubstringTest(void) {
    int errorCode = 0;

    bool firstTest = findSubstring("12345", 5, "34", &errorCode) == 2;
    bool secondTest = findSubstring("12345", 5, "35", &errorCode) == -1;
    bool thirdTest = findSubstring("abcde", 5, "abcde", &errorCode) == 0;
    bool fourthTest = findSubstring("1234", 4, "12345", &errorCode) == -1;

    return firstTest && secondTest && thirdTest && fourthTest;
}

bool fileFindSubstringTest(void) {
    int errorCode = 0;

    bool firstTest = fileFindSubstring("test.txt", "tetatet face 123", &errorCode) == 61;
    bool secondTest = fileFindSubstring("test.txt", "tetatet face 123 123", &errorCode) == 106;

    return firstTest && secondTest;
}

bool substringTest(void) {
    return findSubstringTest() && fileFindSubstringTest();
}