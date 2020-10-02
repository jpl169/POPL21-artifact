ELEMvsFLOAT=""
ELEMvsDOUBLE=""
INTERNvsFLOAT=""
INTERNvsDOUBLE=""

echo "LOG"
OUTPUT=$(./myLog)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "LOG2"
OUTPUT=$(./myLog2)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "LOG10"
OUTPUT=$(./myLog10)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "EXP"
OUTPUT=$(./myExpv2)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "EXP2"
OUTPUT=$(./myExp2v2)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "EXP10"
OUTPUT=$(./myExp10v2)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "SINPI"
OUTPUT=$(./mySinpi)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "COSPI"
OUTPUT=$(./myCospi)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "SQRT"
OUTPUT=$(./mySqrt)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "
echo ""

echo "CBRT"
OUTPUT=$(./myCbrt)
echo "${OUTPUT}"
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]}"
ELEMvsDOUBLE+="${NUMBERS[1]}"
INTERNvsFLOAT+="${NUMBERS[2]}"
INTERNvsDOUBLE+="${NUMBERS[3]}"
echo ""

echo "AVERAGE:"
echo "Speedup of elementary function"
AVERAGE1=$(echo "(${ELEMvsFLOAT// /+}) / 10.0" | bc -l)
echo "Over Float: ${AVERAGE1}"
AVERAGE2=$(echo "(${ELEMvsDOUBLE// /+}) / 10.0" | bc -l)
echo "Over Double: ${AVERAGE1}"
echo "Speedup of interval computation"
AVERAGE3=$(echo "(${INTERNvsFLOAT// /+}) / 10.0" | bc -l)
echo "Over Float: ${AVERAGE3}"
AVERAGE4=$(echo "(${INTERNvsDOUBLE// /+}) / 10.0" | bc -l)
echo "Over Double: ${AVERAGE4}"
