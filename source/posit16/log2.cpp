#include "posit16_math.h"
#include "log2.h"

posit16_t log2(posit16_t x) {
    if (x.v == 0x0 || x.v >= 0x8000) {
        // If x == 0, NaR, or negative, then resutl should be NaR
        x.v = 0x8000;
        return x;
    }
    
    // Extract exponent and mantissa (where mantissa is between [1, 2))
    int m;
    double fx = frexp(convertP16ToDouble(x), &m);
    fx *= 2.0;
    m--;
    
    // Cody and Waite Transformation on input
    double dx = fx;
    double codyX = (dx - 1) / (dx + 1);

    double codyX2 = codyX * codyX;
    // Now compute polynomial
    double y = C_1_9;
    y *= codyX2;
    y += C_1_7;
    y *= codyX2;
    y += C_1_5;
    y *= codyX2;
    y += C_1_3;
    y *= codyX2;
    y += C_1_1;
    y *= codyX;
    y += (double)m;
    
    return convertDoubleToP16(y);
}

double log2Internal(double dx) {
    dint ch;
    ch.d = dx;
    if (ch.x > 0x7FF0000000000000 || ch.x == 0) {
        // If x == 0, NaR, or negative, then resutl should be NaR
        return 0.0;
    }
    
    // Extract exponent and mantissa (where mantissa is between [1, 2))
    int m;
    double fx = frexp(dx, &m);
    fx *= 2.0;
    m--;
    
    // Cody and Waite Transformation on input
    double codyX = (fx - 1) / (fx + 1);

    double codyX2 = codyX * codyX;
    // Now compute polynomial
    double y = C_1_9;
    y *= codyX2;
    y += C_1_7;
    y *= codyX2;
    y += C_1_5;
    y *= codyX2;
    y += C_1_3;
    y *= codyX2;
    y += C_1_1;
    y *= codyX;
    y += (double)m;
    
    return y;
}
