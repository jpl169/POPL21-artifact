#include "posit16_math.h"
#include "cospi.h"

posit16_t cospi(posit16_t x) {
    if (x.v == 0x8000) {
        // Take care of NaN
        x.v = 0x8000;
        return x;
    }
    
    double dx = convertP16ToDouble(x);
    double modifier = 1;

    // cos(-x) = cos(x)
    if (dx < 0.0f) dx = -1 * dx;
    
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf(dx, &intPart);
    int iIntPart = intPart;
    
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
    
    // cos(pi - x) = -cos(x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
        modifier *= -1;
    }
    
    double y = 0;
    if (frac <= R_1_ub) {
        y = C_1_0;
    } else if (frac < R_3_lb) {
        double xSquared = frac * frac;
        y = C_2_8;
        y *= xSquared;
        y += C_2_6;
        y *= xSquared;
        y += C_2_4;
        y *= xSquared;
        y += C_2_2;
        y *= xSquared;
        y += C_2_0;
    } else {
        y = C_3_0;
    }
    
    y *= modifier;
    return convertDoubleToP16(y);
}

double cospiInternal(double dx) {
    dint ch;
    ch.d = dx;
    if ((ch.x & 0x7FFFFFFFFFFFFFFF) > 0x7FF0000000000000) {
        return 0.0/0.0;
    }
    
    double modifier = 1;

    // cos(-x) = cos(x)
    if (dx < 0.0f) dx = -1 * dx;
    
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf(dx, &intPart);
    int iIntPart = intPart;
    
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
    
    // cos(pi - x) = -cos(x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
        modifier *= -1;
    }
    
    double y = 0;
    if (frac <= R_1_ub) {
        y = C_1_0;
    } else if (frac < R_3_lb) {
        double xSquared = frac * frac;
        y = C_2_8;
        y *= xSquared;
        y += C_2_6;
        y *= xSquared;
        y += C_2_4;
        y *= xSquared;
        y += C_2_2;
        y *= xSquared;
        y += C_2_0;
    } else {
        y = C_3_0;
    }
    
    y *= modifier;
    return y;
}
