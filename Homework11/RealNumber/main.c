#include <stdio.h>
#include "lexer.h"
#include "lexerTest.h"

int main(int argc, char **argv) {
    if (!lexerTest()) {
        printf("Tests Failed");
        return 1;
    }
    
    return 0;
}