objects = log2 log sinpi cospi sqrt

all: $(objects)

$(objects): %: %.cpp
	g++ -std=c++14 -I$(SOFTPOSITPATH)/source/include -I../../include/ $^ -lm $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a ../../lib/posit16MathLib.a -o $@


clean:
	rm -rf $(objects) *.dSYM
