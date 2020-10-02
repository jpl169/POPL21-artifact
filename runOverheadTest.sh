#!/bin/bash
ResultPath="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
ResultPath="${ResultPath}/OverheadTestResult.txt"

echo -e "\033[1mBuilding math libraries\033[0m"
make -s clean
make -s

echo -e "\033[1mMeasuring bfloat16 math library speed\033[0m"
echo -e "Measuring bfloat16 math library speed" >> $ResultPath
cd overheadtest/bfloat16
make -s clean
make -s
./runAll.sh >> $ResultPath
make -s clean
echo -e "" >> $ResultPath
echo -e "" >> $ResultPath

echo -e "\033[1mMeasuring posit16 math library speed\033[0m"
echo -e "Measuring posit16 math library speed" >> $ResultPath
cd ../posit16
make -s clean
make -s
./runAll.sh >> $ResultPath
make -s clean
echo -e "" >> $ResultPath
echo -e "" >> $ResultPath

echo -e "\033[1mMeasuring float math library speed\033[0m"
echo -e "Measuring float math library speed" >> $ResultPath
echo -e "This make 10-20 minutes to complete"
cd ../float
make -s clean
make -s
./runAll.sh >> $ResultPath
make -s clean

cd ../..
