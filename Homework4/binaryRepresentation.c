#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void columnAddition(short *first, short *second, int numberDigits) {
    short *sum = (short*)(calloc(numberDigits, sizeof(short)));
    if (sum == NULL) {
        return;
    }

    bool anyRemainder = false;
    for (int i = numberDigits - 1; i >= 0; --i) {
        if (first[i] && second[i]) {
            sum[i] = anyRemainder ? 1 : 0;
            anyRemainder = true;
        } else {
            if (anyRemainder && (first[i] || second[i])) {
                sum[i] = 0;
                anyRemainder = true;
            } else {
                sum[i] = (anyRemainder || first[i] || second[i]
                ? (sum[i] = 1)
                : (sum[i] = 0) 
                );
                anyRemainder = false;
            }
        }
    }

    return sum;
}

void binaryRepresentation(int number, int numberDigits, short* representation) {
    number = number > 0 ? number : (int)pow(2, numberDigits) + number;

    for (int i = numberDigits - 1; i >= 0; --i) {
        representation[i] = number & 1;
        number = number >> 1;
    }
} 

int decimalRepresentation(int numberDigits, short *binary) {
    int sum = 0;
    int current = 1;

    for (int i = numberDigits - 1; i > 0; ++i) {
        sum += binary[i] * current;
        current <<= 1;
    }

    sum -= binary[0] * current;

    return sum;
}

int main() {
    int x = -8;
    int y = -10;
    short *check1 = (short*)(calloc(4, sizeof(short)));
    short *check2 = (short*)(calloc(4, sizeof(short)));
    binaryRepresentation(x, 6, check1);
    binaryRepresentation(y, 6, check2);

    for(int i = 0; i < 6; ++i) {
        printf("%d", check1[i]);
    }
    printf("\n");
    for(int i = 0; i < 6; ++i) {
        printf("%d", check2[i]);
    }
    printf("\n");

   /* for(int i = 0; i < 4; ++i) {
        printf("%d", check[i]);
    }
    int checkint = decimalRepresentation(4, check);
    printf("%d", checkint);*/
    short *check = columnAddition(check1, check2, 6);
    for(int i = 0; i < 6; ++i) {
        printf("%d", check[i]);
    }

    return 0;
}