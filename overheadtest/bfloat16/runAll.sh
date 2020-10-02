ELEMvsFLOAT=""
ELEMvsDOUBLE=""
INTERNvsFLOAT=""
INTERNvsDOUBLE=""

OUTPUT=$(./myLog)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./myLog2)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./myLog10)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./myExp)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./myExp2)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./myExp10)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./mySinpi)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./myCospi)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./mySqrt)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]} "
ELEMvsDOUBLE+="${NUMBERS[1]} "
INTERNvsFLOAT+="${NUMBERS[2]} "
INTERNvsDOUBLE+="${NUMBERS[3]} "

OUTPUT=$(./myCbrt)
NUMBERS=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
NUMBERS=($NUMBERS)
ELEMvsFLOAT+="${NUMBERS[0]}"
ELEMvsDOUBLE+="${NUMBERS[1]}"
INTERNvsFLOAT+="${NUMBERS[2]}"
INTERNvsDOUBLE+="${NUMBERS[3]}"

AVERAGE1=$(echo "(${ELEMvsFLOAT// /+}) / 10.0" | bc -l)
ELEMvsFLOAT+=" ${AVERAGE1}"
AVERAGE2=$(echo "(${ELEMvsDOUBLE// /+}) / 10.0" | bc -l)
ELEMvsDOUBLE+=" ${AVERAGE2}"
AVERAGE3=$(echo "(${INTERNvsFLOAT// /+}) / 10.0" | bc -l)
INTERNvsFLOAT+=" ${AVERAGE3}"
AVERAGE4=$(echo "(${INTERNvsDOUBLE// /+}) / 10.0" | bc -l)
INTERNvsDOUBLE+=" ${AVERAGE4}"

echo "${ELEMvsFLOAT}"
echo "${ELEMvsDOUBLE}"
echo "${INTERNvsFLOAT}"
echo "${INTERNvsDOUBLE}"
