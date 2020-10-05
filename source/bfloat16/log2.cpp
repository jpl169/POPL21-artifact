#include "bfloat16_math.hpp"
#include "log2.h"

bfloat16 mylog2(bfloat16 x) {
    // If x == 0, then it should be -inf
    if (x.val == 0x0 || x.val == 0x8000) {
        x.val = 0xFF80;
        return x;
    }

    // If x == inf, then it should be infinity
    if (x.val == 0x7f80) {
        return x;
    }
    
    // If x == NaN or negative, then it should be NaN
    if (x.val > 0x7F80) {
        x.val = 0xFFFF;
        return x;
    }

    float fInput = (float)x;
    
    // Extract exponent and mantissa (where mantissa is between [1, 2)
    int m;
    float fx = frexpf(fInput, &m);
    fx *= 2.0;
    m--;
    
    // Cody and Waite Transformation on input
    double dx = (double)fx;
    double codyX = (dx - 1) / (dx + 1);
    double codyX2 = codyX * codyX;
    
    // Now compute polynomial
    double y = C_1_5;
    y *= codyX2;
    y += C_1_3;
    y *= codyX2;
    y += C_1_1;
    y *= codyX;
    y += (double)m;
    return y;
}

double mylog2Internal(float x) {
    fx input;
    input.f = x;
    
    // If x == 0, then it should be -inf
    if (input.x == 0x0 || input.x == 0x80000000) {
        input.x = 0xFF800000;
        return input.f;
    }

    // If x == inf, then it should be infinity
    if (input.x == 0x7f800000) {
        return x;
    }
    
    // If x == NaN or negative, then it should be NaN
    if (input.x > 0x7F800000) {
        input.x = 0xFFFFFFFF;
        return input.f;
    }
    
    
    // Extract exponent and mantissa (where mantissa is between [1, 2)
    int m;
    float fx = frexpf((float)x, &m);
    fx *= 2.0;
    m--;
    
    // Cody and Waite Transformation on input
    double dx = (double)fx;
    double codyX = (dx - 1) / (dx + 1);
    double codyX2 = codyX * codyX;
    
    // Now compute polynomial
    double y = C_1_5;
    y *= codyX2;
    y += C_1_3;
    y *= codyX2;
    y += C_1_1;
    y *= codyX;
    y += (double)m;
    return y;
}
