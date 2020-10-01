#include "posit16_math.h"
#include <x86intrin.h>

int main(int argc, char** argv) {
    unsigned long long count = 0;

    unsigned long long ourTime = 0;
    unsigned long long ourInternalTime = 0;

    for (int l = 0; l < 30; l++) {
        for (int i = 0; i < 0x10000; i++) {
            posit16_t x = castP16(i);
            unsigned int dummy;
            unsigned long long t1 = __rdtscp(&dummy);
            posit16_t bres = exp10(x);
            unsigned long long t2 = __rdtscp(&dummy);
            ourTime += (t2 - t1);
            
            double dx = convertP16ToDouble(x);
            t1 = __rdtscp(&dummy);
            double internalRes = exp10Internal(dx);
            t2 = __rdtscp(&dummy);
            ourInternalTime += (t2 - t1);
            
            count++;
        }
    }
    
    printf("Our time average      : %llu\n", ourTime / count);
    printf("Our internal time average : %llu\n", ourInternalTime / count);

}
