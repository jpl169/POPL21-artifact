CXX ?= g++

funcNames = myLog2

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CXX) -std=c++11  -I../../helper/ -I../../include/  $^ ../../lib/floatMathLib.a -lm -o $@

clean:
	rm -rf $(obj) *.dSYM
