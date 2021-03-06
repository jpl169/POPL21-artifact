#include "mpfr.h"
#include "posit16_math.h"
#include "softposit.h"
#include "positMath.h"

#define MPFR_PREC 2000

mpfr_t mval;

posit16_t MpfrCalculateSinpi(posit16_t x) {
    double dx = convertP16ToDouble(x);
    double integral, frac;
    frac = modf(dx, &integral);
    if (frac == 0.0) {
        return castP16(0x0);
    }
    
    mpfr_const_pi(mval, MPFR_RNDN);
    mpfr_mul_d(mval, mval, convertP16ToDouble(x), MPFR_RNDN);
    mpfr_sin(mval, mval, MPFR_RNDN);
    
    // Check for Nan
    if (mpfr_nan_p(mval) != 0) return castP16(0x8000);
    // Check for infinity
    if (mpfr_inf_p(mval) != 0) return castP16(0x8000);
    // Check for 0
    if (mpfr_cmp_d(mval, 0.0) == 0) return castP16(0x0);
    
    if (mpfr_cmp_d(mval, 0) > 0) {
        if (mpfr_cmp_d(mval, pow(2, 27)) > 0) return castP16(0x7fff);
        if (mpfr_cmp_d(mval, 1.5 * pow(2, 25)) >= 0) return castP16(0x7ffe);
        if (mpfr_cmp_d(mval, 1.5 * pow(2, 24)) > 0) return castP16(0x7ffd);
        if (mpfr_cmp_d(mval, pow(2, 24)) >= 0) return castP16(0x7ffc);
        
        
        if (mpfr_cmp_d(mval, pow(2, -27)) < 0) return castP16(0x0001);
        if (mpfr_cmp_d(mval, 1.5 * pow(2, -26)) <= 0) return castP16(0x0002);
        if (mpfr_cmp_d(mval, 1.5 * pow(2, -25)) < 0) return castP16(0x0003);
        if (mpfr_cmp_d(mval, pow(2, -24)) <= 0) return castP16(0x0004);
    } else {
        if (mpfr_cmp_d(mval, -pow(2, 27)) < 0) return castP16(0x8001);
        if (mpfr_cmp_d(mval, -1.5 * pow(2, 25)) <= 0) return castP16(0x8002);
        if (mpfr_cmp_d(mval, -1.5 * pow(2, 24)) < 0) return castP16(0x8003);
        if (mpfr_cmp_d(mval, -pow(2, 24)) <= 0) return castP16(0x8004);
        
        if (mpfr_cmp_d(mval, -pow(2, -27)) > 0) return castP16(0xffff);
        if (mpfr_cmp_d(mval, -1.5 * pow(2, -26)) >= 0) return castP16(0xfffe);
        if (mpfr_cmp_d(mval, -1.5 * pow(2, -25)) > 0) return castP16(0xfffd);
        if (mpfr_cmp_d(mval, -pow(2, -24)) >= 0) return castP16(0xfffc);
    }
    
    long exp;
    double fr = mpfr_get_d_2exp(&exp, mval, MPFR_RNDN);
    long origExp = exp;
    fr *= 2;
    exp--;
    if (exp < 0) {
        exp *= -1;
        exp--;;
    }
    exp >>= 1;
    long p = 13 - exp;
    mpfr_t r;
    mpfr_init2(r, p);
    mpfr_set(r, mval, MPFR_RNDN);
    double retVal = mpfr_get_d(r, MPFR_RNDN);
    mpfr_clear(r);
    return convertDoubleToP16(retVal);
}

int main(int argc, char** argv) {
    mpfr_init2(mval, MPFR_PREC);
    int wrongDoubleCount = 0;
    int wrongMinefieldCount = 0;
    int count = 0;

    for (; count < 0x10000; count++) {
        posit16_t x = castP16(count);
        posit16_t bres = sinpi(x);
        posit16_t bmy = MpfrCalculateSinpi(x);
        posit16_t mineRes = p16_sinpi(x);
        
        if (!p16_eq(bres, bmy)) wrongDoubleCount++;
        if (!p16_eq(bres, mineRes)) wrongMinefieldCount++;
    }
    
    if (wrongDoubleCount == 0) printf("Function returns correct values for all inputs\n");
    else printf("Found %d/%d values that did not calculate correctly\n", wrongDoubleCount, count);
    if (wrongMinefieldCount > 0) printf("Posit-Math's mlib computes %d/%d values incorrectly\n", wrongMinefieldCount, count);
    
    mpfr_clear(mval);
}
