#include <stdio.h>
#include <limits.h>

int main() {
    double myDouble = 3.14159265359;
    int numDigits = 0;
    int myInt;
    while (1) {
        numDigits++;
        int factor = 1;
        for (int i = 0; i < numDigits; i++) {
            factor *= 10;
        }
        if (myDouble >= (double)INT_MAX / factor) {
            factor = (int)(LONG_MAX / myDouble);
        }
        myInt = (int)(myDouble * factor);
        if (myInt % factor == 0) {
            break; // If the integer value is precise, exit the loop
        }
    }
    printf("Original double: %f\n", myDouble);
    printf("Integer with all decimal digits: %d\n", myInt);
    return 0;
}