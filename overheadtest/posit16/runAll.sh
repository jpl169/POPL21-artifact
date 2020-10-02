OURvsSPM=""

echo "COSPI"
OUTPUT=$(./cospi)
echo "${OUTPUT}"
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER} "
echo ""

echo "LOG"
OUTPUT=$(./log)
echo "${OUTPUT}"
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER} "
echo ""

echo "LOG2"
OUTPUT=$(./log2)
echo "${OUTPUT}"
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER} "
echo ""

echo "SINPI"
OUTPUT=$(./sinpi)
echo "${OUTPUT}"
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER} "
echo ""

echo "SQRT"
OUTPUT=$(./sqrt)
echo "${OUTPUT}"
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER}"
echo ""

echo "AVERAGE:"
AVERAGE=$(echo "(${OURvsSPM// /+}) / 5.0" | bc -l)
echo "Speedup over SoftPosit-Math: ${AVERAGE}"
