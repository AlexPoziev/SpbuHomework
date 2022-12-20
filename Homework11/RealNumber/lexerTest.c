#include "lexerTest.h"
#include "lexer.h"

bool realNumberTest(void) {
    bool firstTest = isRealNumber("123");
    bool secondTest = isRealNumber("123.1");
    bool thirdTest = isRealNumber("123e+1");
    bool fourthTest = isRealNumber("123e-1");
    bool fifthTest = isRealNumber("123.2e1");
    bool sixthTest = isRealNumber("123.2e-1");

    return firstTest && secondTest && thirdTest && fourthTest
            && fifthTest && sixthTest;
}

bool notRealNumberTest(void) {
    bool firstTest = !isRealNumber("");
    bool secondTest = !isRealNumber("123.");
    bool thirdTest = !isRealNumber("123e");
    bool fourthTest = !isRealNumber("123e-1.1");
    bool fifthTest = !isRealNumber("123.e");
    bool sixthTest = !isRealNumber("123e.");
    bool seventhTest = !isRealNumber("e");
    bool eighthTest = !isRealNumber("123e.");
    bool ninthTest = !isRealNumber(".123");

    return firstTest && secondTest && thirdTest && fourthTest && fifthTest
            && sixthTest && seventhTest && eighthTest && ninthTest;
}

bool lexerTest(void) {
    return realNumberTest() && notRealNumberTest();
}