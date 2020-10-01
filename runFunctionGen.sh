#!/bin/bash

echo -e "\033[1mCompiling bfloat16 function generator...\033[0m"
cd functiongen/bfloat16/full
make -s clean
make -s
echo -e "\033[1mSynthesizing bfloat16 functions \033[0m"
./runAll.sh
make -s clean

echo -e "\033[1mCompiling posit16 function generator... \033[0m"
cd ../../posit16/full
make -s clean
make -s
echo -e "\033[1mSynthesizing posit16 functions \033[0m"
./runAll.sh
make -s clean

echo -e "\033[1mCompiling float function generator... \033[0m"
cd ../../float/sampling
make -s clean
make -s
echo -e "\033[1mSynthesizing float functions \033[0m"
./runAll.sh
make -s clean

cd ../../..
