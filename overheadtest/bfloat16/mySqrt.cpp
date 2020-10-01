#include "bfloat16.hpp"
#include "bfloat16_math.hpp"
#include <math.h>
#include <x86intrin.h>

bfloat16 mySqrtTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    bfloat16 result = mysqrt(x);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 mlibSqrtTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    bfloat16 result = sqrtf((float)x);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 doubleSqrtTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    bfloat16 result = sqrt((double)x);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}



bfloat16 mySqrtInternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    float input = (float)x;
    unsigned long long t1 = __rdtscp(&dummy);
    double result = mysqrtInternal(input);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 mlibSqrtInternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    float input = (float)x;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = sqrtf(input);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 doubleSqrtInternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    double input = (double)x;
    unsigned long long t1 = __rdtscp(&dummy);
    double result = sqrt(input);
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
            bfloat16 bres = mySqrtTest(x, myTime);
            bfloat16 bfy = mlibSqrtTest(x, mlibTime);
            bfloat16 bdy = doubleSqrtTest(x, doubleTime);
            if (x.val == 0xFFFF) break;
        }
    }
    printf("Average time for my function   = %llu cycles\n", myTime / count);
    printf("Average time for mlib function = %llu cycles\n", mlibTime / count);
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
            bfloat16 bres = mySqrtInternalTest(x, myTime);
            bfloat16 bfy = mlibSqrtInternalTest(x, mlibTime);
            bfloat16 bdy = doubleSqrtInternalTest(x, doubleTime);
            if (x.val == 0xFFFF) break;
        }
    }
    printf("\n\nInternal Test\n");
    printf("Average time for my function     = %llu cycles\n", myTime / count);
    printf("Average time for float function  = %llu cycles\n", mlibTime / count);
    printf("Average time for double function = %llu cycles\n", doubleTime / count);
    printf("\n\n");
}
