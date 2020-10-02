OURvsSPM=""

OUTPUT=$(./cospi)
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER} "

OUTPUT=$(./log)
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER} "

OUTPUT=$(./log2)
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER} "

OUTPUT=$(./sinpi)
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER} "

OUTPUT=$(./sqrt)
NUMBER=$(echo "${OUTPUT}" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
OURvsSPM+="${NUMBER}"

AVERAGE=$(echo "(${OURvsSPM// /+}) / 5.0" | bc -l)
OURvsSPM+=" ${AVERAGE}"
echo "${OURvsSPM}"
