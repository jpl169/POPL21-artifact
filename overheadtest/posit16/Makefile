CXX ?= g++

objects = log2 log sinpi cospi sqrt

all: $(objects)

$(objects): %: %.cpp
	$(CXX) -std=c++14 -I$(SOFTPOSITPATH)/source/include -I$(SOFTPOSITMATHPATH)/include -I../../include/ $^ -lm ../../lib/posit16MathLib.a $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a $(SOFTPOSITMATHPATH)/build/softposit_math.a -o $@


clean:
	rm -rf $(objects) *.dSYM
