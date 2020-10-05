CXX ?= g++

funcNames = myLog2 myLog myLog10 mySinpi myCospi mySqrt myCbrt myExp myExp2 myExp10

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CXX) -std=c++14 $^ ../../lib/bfloat16MathLib.a -lm -lmpfr -lgmp -I../../helper/ -I../../include/ -o $@

clean:
	rm -rf $(obj) *.dSYM
