#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

double linePower(double base, int degree) {
    if (degree == 0 || base == 1) {
        return 1;
    }
    
    double power = 1.0;
    
    if (degree > 0) {
        for (int i = 0; i < degree; ++i) {
            power *= base;
        }
    }
    if (degree < 0) {
        for (int i = 0; i > degree; --i) {
            power /= base;
        }
    }
    
    return power;
}

double fastPower(double base, int degree) {
    if (base == 0.0 || degree == 0) {
        return 1;
    }
    if (degree < 0) {
        return 1 / fastPower (base, -degree);
    }
    
    return ((degree % 2 == 0) ? (fastPower(base * base, degree / 2)) : (base * fastPower(base * base, (degree - 1) / 2)));
}

bool correctTestFast(void) {
    return fastPower(1.0, -1) == 1 && fastPower(2.5, -2) == 0.16 && fastPower(-100.0, 2) == 10000.0 && fastPower(-10.0, 3) == -1000.0 && fastPower(0.0, 0) == 1.0;
}

bool correctTestLine(void) {
    return linePower(1.0, -1) == 1 && linePower(2.5, -2) == 0.16 && linePower(-100.0, 2) == 10000.0 && linePower(-10.0, 3) == -1000.0 && linePower(0, 0) == 1.0;
}

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        if (!strcmp(argv[1], "--test")) {
            if (!correctTestFast() || !correctTestLine()) {
                printf("lineAndLogPow tests: Failed");
                return 1;
            }
            
            printf("lineAndLogPow tests: Passed");
            
            return 0;
        }
    }
    
    printf("Print base and degree separated by a space: ");
    double base = 0.0;
    int degree = 0;
    scanf("%lf %d", &base, &degree);
    
    clock_t start_t = clock();
    printf("Power by fast algorithm: %g \n", fastPower(base, degree));
    clock_t end_t = clock();
    printf("Time: %f seconds \n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    
    start_t = clock();
    printf("Power by linear algorithm: %g \n", linePower(base, degree));
    end_t = clock();
    printf("Time: %f seconds \n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    
    return 0;
}
