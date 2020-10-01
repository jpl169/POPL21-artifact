#include "PolySynth.h"
#include "Elementary.h"

template <>
float Elementary<float>::MpfrCalculateFunction(float x) {
    float mlibLog2 = log2((double)x);
    return mlibLog2;
}

template <>
bool Elementary<float>::ComputeSpecialCase(float x, float& res) {
    floatX fx;
    fx.f = x;
    if (x == 0.0) {
        res = -1.0/0.0;
        return true;
    } else if (fx.x == 0x7F800000) {
        res = x;
        return true;
    } else if (fx.x > 0x7F800000) {
        fx.x = 0x7FFFFFFF;
        res = fx.f;
        return true;
    }
    
    return false;
}

template <>
double Elementary<float>::RangeReduction(float x, double& modifier) {
    // Extract exponent and mantissa (where mantissa is between [1, 2)
    int m;
    float fx = frexpf(x, &m);
    fx *= 2.0; m--;
    double dx = fx;
    
    // Cody and Waite Transformation on input
    double codyX = (dx - 1.0) / (dx + 1.0);
    modifier = m;
    return codyX;
}
    
template <class T>
double Elementary<T>::RangePropagation(double yp, double modifier) {
    return yp + modifier;
}

template <class T>
double Elementary<T>::ReverseRangePropagation(double y, double modifier) {
    return y - modifier;
}

template <class T>
bool Elementary<T>::FlipLbAndUb(double y) {
    return false;
}

int main(int argc, char** argv) {
    mpfr_init2(mval, 2000);
    
    PolySynth<float, Elementary<float>> fp32log2(SAMPLE, 5000);
    fp32log2.SetUpSamplingOption(0.75, 1.5);
    fp32log2.CalcIntervals();

    do {
        printf("FINDING POLYNOMIALS\n");
        fp32log2.ResetPolynomials();
        
        // If we have more than 20k, then we split the intervals into at most 20k
        // each, and create polynomial for each of them.
        int division = fp32log2.poly->intervalInfo->intervals.size() / 20000 + 1;
        int steps = fp32log2.poly->intervalInfo->intervals.size() / division + 1;
        
        for (int i = steps;
             i < fp32log2.poly->intervalInfo->intervals.size();
             i += steps) {
            fp32log2.FindPolynomialsUntil({1, 3, 5, 7, 9, 11, 13, 15}, i - 1);
        }

        fp32log2.FindPolynomials({1, 3, 5, 7, 9, 11, 13, 15});
        printf("\tCOMPLETED\n\n");
    
        fp32log2.poly->PrintPiecewiseInfo();
    } while (fp32log2.TestAndAddSamplePoints());
    
    fp32log2.PerformErrorAnalysis();
    mpfr_clear(mval);
    return 0;
}


/*
0.00000000000000000000 ~ 0.25447859209759260413
    y = 2.8853900817772486497858608345268294215202331542968750000000000000000000e+00 x^(1)
      + 9.6179669436657877490404189302353188395500183105468750000000000000000000e-01 x^(3)
      + 5.7707793208207980306667650438612326979637145996093750000000000000000000e-01 x^(5)
      + 4.1220553778133633970881533059582579880952835083007812500000000000000000e-01 x^(7)
      + 3.2030869252253291179499683494213968515396118164062500000000000000000000e-01 x^(9)
      + 2.6874298098115873001390241370245348662137985229492187500000000000000000e-01 x^(11)
      + 1.4903758089047020041206792484445031732320785522460937500000000000000000e-01 x^(13)
      + 5.3696016612791974687013407674385234713554382324218750000000000000000000e-01 x^(15)


For inputs in the range of:
0.25447988410259808623 ~ 0.33333330684237905128
    y = 2.8853900475671481196116019418695941567420959472656250000000000000000000e+00 x^(1)
      + 9.6179943989057659070596173478406853973865509033203125000000000000000000e-01 x^(3)
      + 5.7698402170703766422832359239691868424415588378906250000000000000000000e-01 x^(5)
      + 4.1397901784000495917226203346217516809701919555664062500000000000000000e-01 x^(7)
      + 3.0040796181516837837222055895836092531681060791015625000000000000000000e-01 x^(9)
      + 3.9989548081464149076325043097313027828931808471679687500000000000000000e-01 x^(11)
      + -3.0467085372361313311273534054635092616081237792968750000000000000000000e-01 x^(13)
      + 1.1007086662029839096987871016608551144599914550781250000000000000000000e+00 x^(15)
*/
