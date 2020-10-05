#include "bfloat16_math.hpp"
#include "exp.h"

bfloat16 myexp(bfloat16 x) {
    float fInput = (float)x;
    
    // Take care of 0 case
    if (fInput <= -93.0f) {
        return 0.0;
    }
    
    // Take care of infinity case
    if (fInput >= 89.0f) {
        x.val = 0x7F80;
        return x;
    }
    
    // Take care of NaN
    if ((x.val & 0x7FFF) > 0x7F80) {
        return x;
    }
    
    if (fInput <= 3.890991e-03 && fInput >= -1.953125e-03) {
        return 1.0;
    }
    
    double xprime = fInput * 1.442695040888963387004650940070860087871551513671875;
    double intPart;
    double fracPart = modf(xprime, &intPart);
    if (fracPart < 0.0f) {
        fracPart += 1.0;
        intPart -= 1.0;
    }

    double y = C_1_4;
    y *= fracPart;
    y += C_1_3;
    y *= fracPart;
    y += C_1_2;
    y *= fracPart;
    y += C_1_1;
    y *= fracPart;
    y += C_1_0;
    
    return ldexp(y, intPart);

}

double myexpInternal(float x) {
    fx input;
    input.f = x;
    
    // Take care of 0 case
    if (input.f <= -134.0f) {
        return 0.0;
    }
    
    // Take care of infinity case
    if (input.f >= 128.0f) {
        input.x = 0x7F800000;
        return input.f;
    }
    
    // Take care of NaN
    if ((input.x & 0x7FFFFFFF) > 0x7F800000) {
        return x;
    }
    
    if (input.f <= 3.890991e-03 && input.f >= -1.953125e-03) {
        return 1.0;
    }
    
    double xprime = (double)x * 1.442695040888963387004650940070860087871551513671875;
    double intPart;
    double fracPart = modf(xprime, &intPart);
    if (fracPart < 0.0f) {
        fracPart += 1.0;
        intPart -= 1.0;
    }

    double y = C_1_4;
    y *= fracPart;
    y += C_1_3;
    y *= fracPart;
    y += C_1_2;
    y *= fracPart;
    y += C_1_1;
    y *= fracPart;
    y += C_1_0;
    
    return ldexp(y, intPart);
}
