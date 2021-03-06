#include <stdint.h>
#include "math.h"
#include <cstdint>

typedef union {
    double d;
    uint64_t x;
} doubleX;

typedef union {
    float f;
    unsigned int x;
} floatX;

float mylog2(float);

