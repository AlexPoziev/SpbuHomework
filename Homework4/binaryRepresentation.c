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

int main() {
    int x = -5;
    short *check = (short*)(calloc(4, sizeof(short)));
    binaryRepresentation(x, 4, check);
    for(int i = 0; i < 4; ++i) {
        printf("%d", check[i]);
    }

    return 0;
}