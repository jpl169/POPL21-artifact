#include "bfloat16_math.hpp"
#include "exp2.h"

bfloat16 myexp2(bfloat16 x) {
    float fInput = (float)x;
    
    // Take care of 0 case
    if (fInput <= -134.0f) {
        return 0.0f;
    }
     
    // Take care of infinity case
    if (fInput >= 128.0f) {
        x.val = 0x7F80;
        return x;
    }
     
    // Take care of NaN
    if ((x.val & 0x7FFFFFFF) > 0x7F800000) {
        return x.val;
    }
    
    // Take care of when result is 1:
    if (fInput >= -2.8076171875e-03 && fInput <= 2.8076171875e-03) {
        return 1.0f;
    }
     
    // Range Reduction
    double intPart;
    double fracPart = modf(fInput, &intPart);
    if (fracPart < 0.0f) {
        fracPart += 1.0;
        intPart -= 1.0;
    }
    
    // Polynomial approximation
    double y = C_1_4;
    y *= fracPart;
    y += C_1_3;
    y *= fracPart;
    y += C_1_2;
    y *= fracPart;
    y += C_1_1;
    y *= fracPart;
    y += C_1_0;

    // Output compensation
    return ldexp(y, intPart);
}

double myexp2Internal(float x) {
    fx input;
    input.f = x;
    
    // Take care of 0 case
    if (x <= -134.0f) {
        return 0.0;
    }
     
    // Take care of infinity case
    if (x >= 128.0f) {
        input.x = 0x7F800000;
        return input.f;
    }
     
    // Take care of NaN
    if ((input.x & 0x7FFFFFFF) > 0x7F800000) {
        return x;
    }
    
    // Take care of when result is 1:
    if (x >= -2.8076171875e-03 && x <= 2.8076171875e-03) {
        return 1.0f;
    }
     
    // Range Reduction
    double intPart;
    double fracPart = modf(x, &intPart);
    if (fracPart < 0.0f) {
        fracPart += 1.0;
        intPart -= 1.0;
    }
    
    // Polynomial approximation
    double y = C_1_4;
    y *= fracPart;
    y += C_1_3;
    y *= fracPart;
    y += C_1_2;
    y *= fracPart;
    y += C_1_1;
    y *= fracPart;
    y += C_1_0;

    // Output compensation
    return ldexp(y, intPart);
}
