#include "float_math.h"
#include <stdio.h>
#include <math.h>
#include <x86intrin.h>

float myLog2Test(float x, unsigned long long* time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = mylog2(x);
    unsigned long long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    return result;
}

float mlibLog2Test(float x, unsigned long long* time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = log2f(x);
    unsigned long long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    return result;
}

float doubleLog2Test(float x, unsigned long long* time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = log2((double)x);
    unsigned long long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    return result;
}

int main(int argc, char** argv) {
    unsigned long long count = 0;
    unsigned long long myTime = 0;
    unsigned long long mlibTime = 0;
    unsigned long long doubleTime = 0;

    float x;
    floatX xbase;
    for (unsigned long long int i = 0; i < 0x100000000; i++) {
        xbase.x = i;
        x = xbase.f;
        float bres = myLog2Test(x, &myTime);
        float bfy = mlibLog2Test(x, &mlibTime);
        float bdy = doubleLog2Test(x, &doubleTime);
    }

    printf("Speedup of interval computation\n");
    printf("Over Float: %.5f\n", 1.0 * mlibTime / myTime);
    printf("Over Double: %.5f\n\n", 1.0 * doubleTime / myTime);
}
