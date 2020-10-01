#include "bfloat16.hpp"
#include "bfloat16_math.hpp"
#include <math.h>
#include <x86intrin.h>

bfloat16 myCbrtTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    bfloat16 result = mycbrt(x);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 mlibCbrtTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    float input = (float)x;
    bfloat16 result = cbrtf(input);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 doubleCbrtTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    bfloat16 result = cbrt((double)x);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}



bfloat16 myCbrtInternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    float dx = (float)x;
    unsigned long long t1 = __rdtscp(&dummy);
    double result = mycbrtInternal(dx);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 mlibCbrtInternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    float input = (float)x;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = cbrtf(input);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 doubleCbrtInternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    float input = (double)x;
    unsigned long long t1 = __rdtscp(&dummy);
    double result = cbrt(input);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}



int main(int argc, char** argv) {
    unsigned long long count = 0;
    unsigned long long myTime = 0;
    unsigned long long mlibTime = 0;
    unsigned long long doubleTime = 0;
    
    bfloat16 x = 0.0;
    for (int i = 0; i < 30; i++) {
        for (x.val = 0; ; x.val++) {
            count++;
            bfloat16 bres = myCbrtTest(x, myTime);
            bfloat16 bfy = mlibCbrtTest(x, mlibTime);
            bfloat16 bdy = doubleCbrtTest(x, doubleTime);
            if (x.val == 0xFFFF) break;
        }
    }
    printf("Average time for my function     = %llu cycles\n", myTime / count);
    printf("Average time for float function  = %llu cycles\n", mlibTime / count);
    printf("Average time for double function = %llu cycles\n", doubleTime / count);
    printf("Average measured over %llu experiments\n", count);
    
    
    count = 0;
    myTime = 0;
    mlibTime = 0;
    doubleTime = 0;
    
    x = 0.0;
    for (int i = 0; i < 30; i++) {
        for (x.val = 0; ; x.val++) {
            count++;
            bfloat16 bres = myCbrtInternalTest(x, myTime);
            bfloat16 bfy = mlibCbrtInternalTest(x, mlibTime);
            bfloat16 bdy = doubleCbrtInternalTest(x, doubleTime);
            if (x.val == 0xFFFF) break;
        }
    }
    printf("\n\nInternal Test\n");
    printf("Average time for my function     = %llu cycles\n", myTime / count);
    printf("Average time for float function  = %llu cycles\n", mlibTime / count);
    printf("Average time for double function = %llu cycles\n", doubleTime / count);
    printf("\n\n");
    
    
}
