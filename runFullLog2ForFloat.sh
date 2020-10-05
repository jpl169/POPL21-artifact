#!/bin/bash
ResultPath="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
ResultPath="${ResultPath}/LibTestFulLog2Float.txt"

rm -rf $ResultPath
echo -e "\033[1mBuilding math libraries \033[0m"
make -s clean
make -s

echo -e "Result will be outputted to \033[1m${ResultPath}\033[0m"
echo -e ""

echo -e "\033[1mTesting float math library correctness \033[0m"
echo -e "Testing float math library correctness" >> $ResultPath
echo -e "This may take 2-3 hours to complete"
cd ../float
make -s clean
make -s
./runFullInput.sh >> $ResultPath
make -s clean


cd ../..
