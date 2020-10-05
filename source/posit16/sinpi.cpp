#include "posit16_math.h"
#include "sinpi.h"

posit16_t sinpi(posit16_t x) {
    if (x.v == 0x8000) {
        // Take care of NaN
        x.v = 0x8000;
        return x;
    }
    
    double dx = convertP16ToDouble(x);
    double modifier = 1;

    // sin(-x) = -sin(x)
    if (dx < 0.0f) {
        dx = -1.0 * dx;
        modifier *= -1;
    }
    
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf(dx, &intPart);
    int iIntPart = intPart;
    
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
    
    // sin(x) = sin(pi - x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
    }
    double fracPart = frac;
    double y = 0;
    if (fracPart <= R_1_ub) {
        y = C_1_1 * fracPart;
    } else {
        double xSquared = fracPart * fracPart;
        y = C_2_9;
        y *= xSquared;
        y += C_2_7;
        y *= xSquared;
        y += C_2_5;
        y *= xSquared;
        y += C_2_3;
        y *= xSquared;
        y += C_2_1;
        y *= fracPart;
    }
    
    y *= modifier;
    return convertDoubleToP16(y);
}

double sinpiInternal(double dx) {
    dint ch;
    ch.d = dx;
    if ((ch.x & 0x7FFFFFFFFFFFFFFF) > 0x7FF0000000000000) {
        return 0.0/0.0;
    }
    
    double modifier = 1;

    // sin(-x) = -sin(x)
    if (dx < 0.0f) {
        dx = -1.0 * dx;
        modifier *= -1;
    }
    
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf(dx, &intPart);
    int iIntPart = intPart;
    
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
    
    // sin(x) = sin(pi - x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
    }
    double fracPart = frac;
    double y = 0;
    if (fracPart <= R_1_ub) {
        y = C_1_1 * fracPart;
    } else {
        double xSquared = fracPart * fracPart;
        y = C_2_9;
        y *= xSquared;
        y += C_2_7;
        y *= xSquared;
        y += C_2_5;
        y *= xSquared;
        y += C_2_3;
        y *= xSquared;
        y += C_2_1;
        y *= fracPart;
    }
    
    y *= modifier;
    return y;
}
