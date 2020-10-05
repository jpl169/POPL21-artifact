CXX ?= g++

funcNames = myLog2 myLog2short

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CXX) -std=c++11  -I../../helper/ -I../../include/  $^ ../../lib/floatMathLib.a -lm -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
