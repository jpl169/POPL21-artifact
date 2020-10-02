#!/bin/bash
echo "\033[1mBuilding math libraries\033[0m"
make -s clean
make -s

echo "\033[1mMeasuring bfloat16 math library speed\033[0m"
cd overheadtest/bfloat16
make -s clean
make -s
./runAll.sh
make -s clean

echo "\033[1mMeasuring posit16 math library speed\033[0m"
cd ../posit16
make -s clean
make -s
./runAll.sh
make -s clean

echo "\033[1mMeasuring float math library speed\033[0m"
cd ../float
make -s clean
make -s
./runAll.sh
make -s clean

cd ../..
