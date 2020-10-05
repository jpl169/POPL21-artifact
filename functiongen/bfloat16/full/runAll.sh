#!/bin/bash
rm -rf headers && mkdir headers
echo -e "EXP FUNCTION"
./Exp headers/exp.h
echo -e "EXP2 FUNCTION"
./Exp2 headers/exp2.h
echo -e "EXP10 FUNCTION"
./Exp10  headers/exp10.h
echo -e "LOG FUNCTION"
./Log headers/log.h
echo -e "LOG2 FUNCTION"
./Log2 headers/log2.h
echo -e "LOG10 FUNCTION"
./Log10 headers/log10.h
echo -e "SINPI FUNCTION"
./Sinpi headers/sinpi.h
echo -e "COSPI FUNCTION"
./Cospi headers/cospi.h
echo -e "CBRT FUNCTION"
./Cbrt headers/cbrt.h
echo -e "SQRT FUNCTION"
./Sqrt headers/sqrt.h
