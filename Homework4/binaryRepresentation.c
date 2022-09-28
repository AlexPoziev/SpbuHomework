#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void binaryRepresentation(int number, int numberDigits, short* representation) {
    number = number > 0 ? number : (int)pow(2, numberDigits) + number;

    for (int i = numberDigits - 1; i >= 0; --i) {
        representation[i] = number & 1;
        number = number >> 1;
    }
} 

int decimalRepresentation(int numberDigits, short *binary) {
    int decimal = 0;
    int current = 1;

    for (int i = 0; i < numberDigits - 1; ++i) {
        decimal += binary[numberDigits - i - 1] * current;
        current <<= 1;
    }

    decimal -= binary[0] * current;

    return decimal;
}

int main() {
    int x = 5;
    short *check = (short*)(calloc(4, sizeof(short)));
    binaryRepresentation(x, 4, check);
   /* for(int i = 0; i < 4; ++i) {
        printf("%d", check[i]);
    }*/
    int checkint = decimalRepresentation(4, check);
    printf("%d", checkint);

    return 0;
}