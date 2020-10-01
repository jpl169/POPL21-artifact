objects = log2 log log10 sinpi cospi sqrt exp exp2 exp10

all: $(objects)

$(objects): %: %.cpp
	g++ -std=c++14 -I$(SOFTPOSITPATH)/source/include -I../../include/ $^ -lm $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a ../../lib/posit16MathLib.a -o $@


clean:
	rm -rf $(objects) *.dSYM
