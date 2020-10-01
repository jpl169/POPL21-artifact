#include "posit16_math.h"
#include "softposit.h"
#include <x86intrin.h>

int main(int argc, char** argv) {
    unsigned long long count = 0;
    
    unsigned long long ourTime = 0;
    unsigned long long ourInternalTime = 0;
    unsigned long long minefieldTime = 0;

    for (int l = 0; l < 30; l++) {
        for (int i = 0; i < 0x10000; i++) {
            posit16_t x = castP16(i);
            unsigned int dummy;
            unsigned long long t1 = __rdtscp(&dummy);
            posit16_t bres = cospi(x);
            unsigned long long t2 = __rdtscp(&dummy);
            ourTime += (t2 - t1);
            
            double dx = convertP16ToDouble(x);
            t1 = __rdtscp(&dummy);
            double internalRes = cospiInternal(dx);
            t2 = __rdtscp(&dummy);
            ourInternalTime += (t2 - t1);
            
            t1 = __rdtscp(&dummy);
            posit16_t mineRes = p16_cospi(x);
            t2 = __rdtscp(&dummy);
            minefieldTime += (t2 - t1);
            
            count++;
        }
    }
    
    printf("Our time average          : %llu\n", ourTime / count);
    printf("Our internal time average : %llu\n", ourInternalTime / count);
    printf("Minefield time average    : %llu\n", minefieldTime / count);
    printf("Our speedup: %.50e\n", 1.0 * minefieldTime / ourTime);
    printf("Our internal speedup: %.50e\n", 1.0 * minefieldTime / ourInternalTime);
}
