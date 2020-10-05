#include "bfloat16_math.hpp"
#include "exp10.h"

bfloat16 myexp10(bfloat16 x) {
    float fInput = (float)x;

    // Take care of when result is 0
    if (fInput <= -40.5f) {
        return 0.0f;
    }

    // Take care of infinity case
    if (fInput >= 38.75f) {
        x.val = 0x7F80;
        return x;
    }
    
    // Take care of NaN
    if ((x.val & 0x7FFF) > 0x7F80) {
        return x;
    }
    
    if ((fInput >= -8.4686279296875e-04) && (fInput <= 1.68609619140625e-03)) {
        // The values in these range return 1.0.
        return 1.0f;
    }
    
    double xprime = fInput * 3.321928094887362181708567732130177319049835205078125;
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

double myexp10Internal(float x) {
    fx input;
    input.f = x;

    // Take care of when result is 0
    if (x <= -40.5f) {
        return 0.0;
    }

    // Take care of infinity case
    if (x >= 38.75f) {
        input.x = 0x7F800000;
        return input.f;
    }
    
    // Take care of NaN
    if ((input.x & 0x7FFFFFFF) > 0x7F800000) {
        return x;
    }
    
    if ((x >= -8.4686279296875e-04) && (x <= 1.68609619140625e-03)) {
        // The values in these range return 1.0.
        return 1.0;
    }
    
    double xprime = x * 3.321928094887362181708567732130177319049835205078125;
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
