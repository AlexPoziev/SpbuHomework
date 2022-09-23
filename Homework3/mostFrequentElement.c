#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void *x_void, const void *y_void) {
    int x = *(int *)x_void;
    int y = *(int *)y_void;
    
    return x - y;
}

int main() {

    return 0;
}