CC = g++

funcNames = myLog2 myLog myLog10 mySinpi myCospi mySqrt myCbrt myExp myExp2 myExp10

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -std=c++14 -I../../helper/ -I../../include/ $^ ../../lib/bfloat16MathLib.a -lm -o $@

clean:
	rm -rf $(obj) *.dSYM
