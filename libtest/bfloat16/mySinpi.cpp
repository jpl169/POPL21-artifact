#include "mpfr.h"
#include "bfloat16_math.hpp"
#include "bfloat16.hpp"
#include <math.h>

#define MPFR_PREC 2000
mpfr_t mval;

double MpfrCalculateSinpi(bfloat16 x) {
    mpfr_const_pi(mval, MPFR_RNDN);
    mpfr_mul_d(mval, mval, (double)x, MPFR_RNDN);
    mpfr_sin(mval, mval, MPFR_RNDN);
    double retVal = mpfr_get_d(mval, MPFR_RNDN);

    if (retVal == 0) return 0.0;
    if (retVal != retVal) {
        return retVal;
    }
    
    if (mpfr_cmp_d(mval, pow(2, -134)) <= 0 && mpfr_cmp_d(mval, -pow(2, -134)) >= 0) {
        return 0;
    }

    long exp;
    double fr = mpfr_get_d_2exp(&exp, mval, MPFR_RNDN);
    fr *= 2;
    exp--;
    
    if (mpfr_cmp_d(mval, 0.0) > 0) {
        if (mpfr_cmp_d(mval, 1.5 * pow(2, -133)) < 0) return pow(2, -133);
        if (mpfr_cmp_d(mval, pow(2, -132)) < 0) return pow(2, -132);

    } else {
        if (mpfr_cmp_d(mval, -1.5 * pow(2, -133)) > 0) return -pow(2, -133);
        if (mpfr_cmp_d(mval, -pow(2, -132)) > 0) return -pow(2, -132);
    }
    
    if (exp >= -132 && exp <= -127) {
        int prec = 134 + exp;
        mpfr_t r;
        mpfr_init2(r, prec);
        mpfr_set(r, mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    } else {
        mpfr_t r;
        mpfr_init2(r, 8);
        mpfr_set(r, mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    }
}

bfloat16 mySinpiTest(bfloat16 x) {
    bfloat16 result = mysinpi(x);
    return result;
}

int main(int argc, char** argv) {
    mpfr_init2(mval, MPFR_PREC);
    int wrongBfloatCount = 0;
    unsigned long long count = 0;

    bfloat16 x = 0.0;
    for (; count < 0x10000; count++) {
        x.val = count;
        bfloat16 bres = mySinpiTest(x);
        bfloat16 bmy = MpfrCalculateSinpi(x);
        
        // if bres is nan and bmy is nan, continue
        if (bres != bres && bmy != bmy) continue;
        if (bres != bmy) wrongBfloatCount++;
    }
    
    if (wrongBfloatCount == 0) printf("Function returns correct values for all inputs\n");
    else printf("Found %d/%llu values that did not calculate correctly\n", wrongBfloatCount, count);
    mpfr_clear(mval);
}
