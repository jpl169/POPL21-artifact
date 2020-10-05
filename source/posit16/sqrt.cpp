#include "posit16_math.h"
#include "sqrt.h"

posit16_t mysqrt(posit16_t x) {
    if (x.v >= 0x8000) {
        x.v = 0x8000;
        return x;
    } else if (x.v == 0x0) {
        return x;
    }
    
    // Extract exponent and mantissa
    int m;
    float fx = frexpf(convertP16ToDouble(x), &m);
    
    if ((m & 0x1) == 0) {
        fx *= 4.0;
        m -= 2;
    } else {
        fx *= 2.0;
        m--;
    }
    
    // Instead of [0.5, 2) make it [1/8, 0.5)
    m >>= 1;
    
    double y = 0;
    
    if (fx <= R_1_ub) {
        y = C_1_6;
        y *= fx;
        y += C_1_5;
        y *= fx;
        y += C_1_4;
        y *= fx;
        y += C_1_3;
        y *= fx;
        y += C_1_2;
        y *= fx;
        y += C_1_1;
        y *= fx;
        y += C_1_0;
    } else {
        y = C_2_6;
        y *= fx;
        y += C_2_5;
        y *= fx;
        y += C_2_4;
        y *= fx;
        y += C_2_3;
        y *= fx;
        y += C_2_2;
        y *= fx;
        y += C_2_1;
        y *= fx;
        y += C_2_0;
    }
    
    y = ldexp(y, m);
    return convertDoubleToP16(y);
}

double mysqrtInternal(double dx) {
    dint ch;
    ch.d = dx;
    if (ch.x >= 0x7FF0000000000000) {
        return 0.0/0.0;
    } else if (dx == 0.0) {
        return dx;
    }
    
    // Extract exponent and mantissa
    int m;
    double fx = frexpf(dx, &m);
    
    if ((m & 0x1) == 0) {
        fx *= 4.0;
        m -= 2;
    } else {
        fx *= 2.0;
        m--;
    }
    
    // Instead of [0.5, 2) make it [1/8, 0.5)
    m >>= 1;
    
    double y = 0;
    
    if (fx <= R_1_ub) {
        y = C_1_6;
        y *= fx;
        y += C_1_5;
        y *= fx;
        y += C_1_4;
        y *= fx;
        y += C_1_3;
        y *= fx;
        y += C_1_2;
        y *= fx;
        y += C_1_1;
        y *= fx;
        y += C_1_0;
    } else {
        y = C_2_6;
        y *= fx;
        y += C_2_5;
        y *= fx;
        y += C_2_4;
        y *= fx;
        y += C_2_3;
        y *= fx;
        y += C_2_2;
        y *= fx;
        y += C_2_1;
        y *= fx;
        y += C_2_0;
    }
    
    y = ldexp(y, m);
    return y;
}
