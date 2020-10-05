#include "bfloat16_math.hpp"
#include "cbrt.h"

bfloat16 mycbrt(bfloat16 x) {
    
    // If x == 0, then it should be 0
    if (x.val == 0x0 || x.val == 0x8000) {
        return x;
    }

    // If x == inf, then it should be infinity
    if ((x.val & 0x7f80) == 0x7f80) {
        return x;
    }
    
    // If x == NaN, then it should be NaN
    if ((x.val & 0x7f80) > 0x7F80) {
        x.val = 0xFFFF;
        return x;
    }

    // Extract exponent and mantissa (where mantissa is between [1, 8))
    int m;
    float rx = frexpf((float)x, &m);
    rx *= 2.0;
    m--;
    
    int leftOver = m % 3;
    if (leftOver != 0) {
        if (leftOver < 0) leftOver += 3;
        
        fx fi;
        fi.x = 0x3f800000 + (leftOver << 23);
        rx *= fi.f;
        m -= leftOver;
    }

    m /= 3;
    if (rx < 0) rx *= -1;
    
    // Now compute polynomial
    double y = C_1_6;
    y *= rx;
    y += C_1_5;
    y *= rx;
    y += C_1_4;
    y *= rx;
    y += C_1_3;
    y *= rx;
    y += C_1_2;
    y *= rx;
    y += C_1_1;
    y *= rx;
    y += C_1_0;
    
    if (x < 0) y *= -1;
    return ldexp(y, m);
}

double mycbrtInternal(float x) {
    fx input;
    input.f = x;
    
    // If x == 0, then it should be -inf
    if (input.x == 0x0 || input.x == 0x80000000) {
        return x;
    }

    // If x == inf, then it should be infinity
    if ((input.x & 0x7f800000) == 0x7f800000) {
        return x;
    }
    
    // If x == NaN or negative, then it should be NaN
    if ((input.x & 0x7f800000) > 0x7F800000) {
        input.x = 0xFFFFFFFF;
        return input.f;
    }
    
    
    // Extract exponent and mantissa (where mantissa is between [1, 8))
    int m;
    float rx = frexpf((float)x, &m);
    rx *= 2.0;
    m--;
    
    int leftOver = m % 3;
    if (leftOver != 0) {
        if (leftOver < 0) leftOver += 3;
        
        fx fi;
        fi.x = 0x3f800000 + (leftOver << 23);
        rx *= fi.f;
        m -= leftOver;
    }

    m /= 3;
    if (rx < 0) rx *= -1;
    
    // Now compute polynomial
    double y = C_1_6;
    y *= rx;
    y += C_1_5;
    y *= rx;
    y += C_1_4;
    y *= rx;
    y += C_1_3;
    y *= rx;
    y += C_1_2;
    y *= rx;
    y += C_1_1;
    y *= rx;
    y += C_1_0;
    
    if (x < 0) y *= -1;
    return ldexp(y, m);
}
