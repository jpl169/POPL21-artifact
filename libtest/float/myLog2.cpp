#include "mpfr.h"
#include "float_math.h"
#include <stdio.h>
#include <math.h>

#define MPFR_PREC 24
mpfr_t mval;

float MpfrCalculateLog2(float x) {
    mpfr_set_d(mval, (float)x, MPFR_RNDN);
    mpfr_log2(mval, mval, MPFR_RNDN);
    double retVal = mpfr_get_d(mval, MPFR_RNDN);

    if (retVal == 0) return 0.0;
    if (retVal != retVal) {
        return retVal;
    }
    
    if (mpfr_cmp_d(mval, pow(2, -150)) <= 0 && mpfr_cmp_d(mval, -pow(2, -150)) >= 0) {
        return 0;
    }

    long exp;
    double fr = mpfr_get_d_2exp(&exp, mval, MPFR_RNDN);
    fr *= 2;
    exp--;
    
    if (mpfr_cmp_d(mval, 0.0) > 0) {
        if (mpfr_cmp_d(mval, 1.5 * pow(2, -149)) < 0) return pow(2, -149);
        if (mpfr_cmp_d(mval, pow(2, -148)) < 0) return pow(2, -148);

    } else {
        if (mpfr_cmp_d(mval, -1.5 * pow(2, -149)) > 0) return -pow(2, -149);
        if (mpfr_cmp_d(mval, -pow(2, -148)) > 0) return -pow(2, -148);
    }
    
    if (exp >= -148 && exp <= -127) {
        int prec = 150 + exp;
        mpfr_t r;
        mpfr_init2(r, prec);
        mpfr_set(r, mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    } else {
        mpfr_t r;
        mpfr_init2(r, 24);
        mpfr_set(r, mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    }
}

float myLog2Test(float x) {
    float result = mylog2(x);
    return result;
}

float mlibLog2Test(float x) {
    float result = log2f(x);
    return result;
}

float doubleLog2Test(float x) {
    float result = log2((double)x);
    return result;
}

int main(int argc, char** argv) {
    mpfr_init2(mval, MPFR_PREC);
    int wrongFloat32Count = 0;
    int wrongFloatCount = 0;
    int wrongDoubleCount = 0;
    unsigned long long count = 0;

    float x;
    floatX xbase;
    for (count = 0x0; count < 0x100000000; count++) {
        xbase.x = count;
        x = xbase.f;
        
        float bres = myLog2Test(x);
        float bmy = MpfrCalculateLog2(x);
        float bfy = mlibLog2Test(x);
        float bdy = doubleLog2Test(x);
        
        // if bres is nan and bmy is nan, continue
        if (bres != bres && bmy != bmy && bfy != bfy && bdy != bdy) continue;
        if (bres != bmy) wrongFloat32Count++;
        if (bfy != bmy) wrongFloatCount++;
        if (bdy != bmy) wrongDoubleCount++;
    }
    
    if (wrongFloat32Count == 0) printf("Function returns correct values for all inputs\n");
    else printf("Found %d/%llu values that did not calculate correctly\n", wrongFloat32Count, count);
    if (wrongFloatCount > 0) printf("Using Glibc's float mlib computes %d/%llu values incorrectly\n", wrongFloatCount, count);
    if (wrongDoubleCount > 0) printf("Using Glibc's double mlib computes %d/%llu values incorrectly\n", wrongDoubleCount, count);
    
    mpfr_clear(mval);
    return 0;
}
