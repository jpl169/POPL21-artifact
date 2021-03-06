#!/bin/bash
ResultPath="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
B16_ResultPath="${ResultPath}/B16OvhdRslt.txt"
P16_ResultPath="${ResultPath}/P16OvhdRslt.txt"
F32_ResultPath="${ResultPath}/F32OvhdRslt.txt"

echo -e "\033[1mBuilding math libraries\033[0m"
make -s clean
make -s

echo -e "\033[1mMeasuring bfloat16 math library speed\033[0m"
cd overheadtest/bfloat16
make -s clean
make -s
./runAll.sh > $B16_ResultPath
make -s clean
cd ../..
python3 bfloatOverheadFull.py
python3 bfloatOverheadInternal.py
echo -e "Output \033[1mbfloatOverheadFull.pdf\033[0m corresponds to Figure 11(a)"
echo -e "Output \033[1mbfloatOverheadInternal.pdf\033[0m corresponds to Figure 11(b)"
echo -e ""

echo -e "\033[1mMeasuring posit16 math library speed\033[0m"
cd overheadtest/posit16
make -s clean
make -s
./runAll.sh > $P16_ResultPath
make -s clean
cd ../..
python3 positOverheadInternal.py
echo -e "Output \033[1mpositOverheadInternal.pdf\033[0m corresponds to Figure 12"
echo -e ""

echo -e "\033[1mMeasuring float math library speed\033[0m"
echo -e "This make 10-20 minutes to complete"
cd overheadtest/float
make -s clean
make -s
./runAll.sh > $F32_ResultPath
make -s clean
echo -e "Output result in \033[1mF32OvhdRslt.txt\033[0m"

cd ../..
