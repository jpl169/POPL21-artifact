#include "bfloat16_math.hpp"
#include "sqrt.h"

bfloat16 mysqrt(bfloat16 x) {
    
    // If x == 0, then it should be 0
    if (x.val == 0x0 || x.val == 0x8000) {
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
    
    
    // Extract exponent and mantissa (where mantissa is between [1, 4))
    int m;
    float fx = frexpf((float)x, &m);
    fx *= 2.0;
    m--;
    
    if ((m & 0x1) == 1) {
        fx *= 2.0;
        m--;
    }
    
    m >>= 1;
    
    // Now compute polynomial
    double y = C_1_4;
    y *= fx;
    y += C_1_3;
    y *= fx;
    y += C_1_2;
    y *= fx;
    y += C_1_1;
    y *= fx;
    y += C_1_0;
    
    return ldexp(y, m);
}

double mysqrtInternal(float x) {
    fx input;
    input.f = x;
    
    // If x == 0, then it should be -inf
    if (input.x == 0x0 || input.x == 0x80000000) {
        return x;
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
    
    
    // Extract exponent and mantissa (where mantissa is between [1, 4))
    int m;
    float fx = frexpf((float)x, &m);
    fx *= 2.0;
    m--;
    
    if ((m & 0x1) == 1) {
        fx *= 2.0;
        m--;
    }
    
    m >>= 1;
    
    // Now compute polynomial
    double y = C_1_4;
    y *= fx;
    y += C_1_3;
    y *= fx;
    y += C_1_2;
    y *= fx;
    y += C_1_1;
    y *= fx;
    y += C_1_0;
    
    return ldexp(y, m);
}
