#!/bin/bash
rm -rf headers && mkdir headers
echo -e "LOG2"
./Log2 headers/log2.h
echo -e "LOG"
./Log headers/log.h
echo -e "LOG10"
./Log10 headers/log10.h
echo -e "SINPI"
./Sinpi headers/sinpi.h
echo -e "COSPI"
./Cospi headers/cospi.h
echo -e "SQRT"
./Sqrt headers/sqrt.h
