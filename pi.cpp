#include <stdio.h>
#include <math.h>
 
//calc pi
int main() {
    double pi = 0;
    for (int i = 0; i < 1000000; i++) {
        pi += pow(-1, i) / (2 * i + 1);
    }
    pi *= 4;
    printf("pi = %f\n", pi);
    return 0;
}