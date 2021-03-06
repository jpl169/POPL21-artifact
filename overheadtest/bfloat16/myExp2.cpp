#include "bfloat16.hpp"
#include "bfloat16_math.hpp"
#include <math.h>
#include <x86intrin.h>

bfloat16 myExp2Test(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    bfloat16 result = myexp2(x);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 mlibExp2Test(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    bfloat16 result = exp2f((float)x);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 doubleExp2Test(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    bfloat16 result = exp2((double)x);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}



bfloat16 myExp2InternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    float input = (float)x;
    unsigned long long t1 = __rdtscp(&dummy);
    double result = myexp2Internal(input);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 mlibExp2InternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    float input = (float)x;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = exp2f(input);
    unsigned long long t2 = __rdtscp(&dummy);
    time += (t2 - t1);
    return result;
}

bfloat16 doubleExp2InternalTest(bfloat16 x, unsigned long long& time) {
    unsigned int dummy;
    double input = (double)x;
    unsigned long long t1 = __rdtscp(&dummy);
    double result = exp2(input);
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
            bfloat16 bres = myExp2Test(x, myTime);
            bfloat16 bfy = mlibExp2Test(x, mlibTime);
            bfloat16 bdy = doubleExp2Test(x, doubleTime);
            if (x.val == 0xFFFF) break;
        }
    }
    printf("Speedup of elementary function\n");
    printf("Over Float: %.5f\n", 1.0 * mlibTime / myTime);
    printf("Over Double: %.5f\n", 1.0 * doubleTime / myTime);
    
    
    count = 0;
    myTime = 0;
    mlibTime = 0;
    doubleTime = 0;

    x = 0.0;
    for (int i = 0; i < 30; i++) {
        for (x.val = 0; ; x.val++) {
            count++;
            bfloat16 bres = myExp2InternalTest(x, myTime);
            bfloat16 bfy = mlibExp2InternalTest(x, mlibTime);
            bfloat16 bdy = doubleExp2InternalTest(x, doubleTime);
            if (x.val == 0xFFFF) break;
        }
    }
    printf("Speedup of interval computation\n");
    printf("Over Float: %.5f\n", 1.0 * mlibTime / myTime);
    printf("Over Double: %.5f\n\n", 1.0 * doubleTime / myTime);
    
    return 0;
}
