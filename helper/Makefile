CXX ?= g++

INCLUDES= -I$(SOFTPOSITPATH)/source/include -I$(SOPLEXPATH)/src
CPP_FLAGS= -O2 --std=c++17 -I../helper/

all: PolyFinder.o IntervalRange.o

%.o: %.cpp
	$(CXX) $(CPP_FLAGS) -c $< -o $@ $(INCLUDES)
	
clean:
	rm -rf *.o *.lp *~ *.dSYM
