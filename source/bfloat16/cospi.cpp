#include "bfloat16_math.hpp"
#include "cospi.h"

bfloat16 mycospi(bfloat16 x) {
    if ((x.val & 0x7FFF) > 0x7F80) {
        // Take care of NaN
        return x;
    }
    
    if ((x.val & 0x7FFF) == 0x7F80) {
        x.val = 0x7FFF;
        return x;
    }
    
    float fInput = (float)x;
    
    if (fInput >= 256.0f || fInput <= -256.0f) {
        return 1.0f;
    }
    
    double modifier = 1;

    // cos(-x) = cos(x)
    if (fInput < 0.0f) fInput = -fInput;
     
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf((double)fInput, &intPart);
    int iIntPart = intPart;
     
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
     
    // cos(pi - x) = -cos(x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
        modifier *= -1;
    }
    
    double fracPart = frac;
    double y = 0;
    if (fracPart <= R_1_ub) {
        y = C_1_0;
    } else if (fracPart < R_3_lb) {
        double xSquared = fracPart * fracPart;
        y = C_2_6;
        y *= xSquared;
        y += C_2_4;
        y *= xSquared;
        y += C_2_2;
        y *= xSquared;
        y += C_2_0;
    } else {
        y = C_3_0;
    }
    
    return y * modifier;
}

double mycospiInternal(float x) {
    fx input;
    input.f = x;
    
    if ((input.x & 0x7FFFFFFF) > 0x7F800000) {
        // Take care of NaN
        return x;
    } else if ((input.x & 0x7FFFFFFF) == 0x7F800000) {
        input.x = 0x7FFFFFFF;
        return input.f;
    } else if (x >= 256.0f || x <= -256.0f) {
        return 1.0f;
    }
    
    double modifier = 1;

    // cos(-x) = cos(x)
    if (x < 0.0f) x = -(float)x;
     
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf((double)x, &intPart);
    int iIntPart = intPart;
     
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
     
    // cos(pi - x) = -cos(x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
        modifier *= -1;
    }
    
    double fracPart = frac;
    double y = 0;
    if (fracPart <= R_1_ub) {
        y = C_1_0;
    } else if (fracPart < R_3_lb) {
        double xSquared = fracPart * fracPart;
        y = C_2_6;
        y *= xSquared;
        y += C_2_4;
        y *= xSquared;
        y += C_2_2;
        y *= xSquared;
        y += C_2_0;
    } else {
        y = C_3_0;
    }
    
    return y * modifier;
}
