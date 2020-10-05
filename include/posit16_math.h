#include "math.h"
#include "softposit.h"
#include <cstdint>

typedef union {
    double d;
    unsigned long long x;
} dint;

posit16_t cospi(posit16_t x);
posit16_t log(posit16_t x);
posit16_t log2(posit16_t x);
posit16_t log10(posit16_t x);
posit16_t sinpi(posit16_t x);
posit16_t mysqrt(posit16_t x);

double cospiInternal(double dx);
double logInternal(double dx);
double log2Internal(double dx);
double log10Internal(double dx);
double sinpiInternal(double dx);
double mysqrtInternal(double dx);
