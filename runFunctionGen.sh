#!/bin/bash
ResultPath="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
ResultPath="${ResultPath}/Functions.txt"

echo -e "\033[1mCompiling bfloat16 function generator...\033[0m"
cd functiongen/bfloat16/full
make -s clean
make -s
echo -e "\033[1mSynthesizing bfloat16 functions \033[0m"
echo -e "Synthesizing bfloat16 functions" >> $ResultPath
./runAll.sh >> $ResultPath
make -s clean

echo -e "\033[1mCompiling posit16 function generator... \033[0m"
cd ../../posit16/full
make -s clean
make -s
echo -e "\033[1mSynthesizing posit16 functions \033[0m"
echo -e "Synthesizing bfloat16 functions" >> $ResultPath
./runAll.sh >> $ResultPath
make -s clean

echo -e "\033[1mCompiling float function generator... \033[0m"
cd ../../float/sampling
make -s clean
make -s
echo -e "\033[1mSynthesizing float functions \033[0m"
echo -e "Synthesizing bfloat16 functions" >> $ResultPath
./runAll.sh >> $ResultPath
make -s clean

cd ../../..
