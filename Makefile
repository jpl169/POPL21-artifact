CXX ?= g++

bf16FNames = log log2 log10 sinpi cospi sqrt cbrt exp exp2 exp10
p16FNames = cospi log log2 log10 sinpi sqrt
floatFNames = log2

bf16SrcDir = source/bfloat16
bf16ObjDir = obj/bfloat16
p16SrcDir = source/posit16
p16ObjDir = obj/posit16
floatSrcDir = source/float
floatObjDir = obj/float
libDir = lib

bf16Src = $(patsubst %, $(bf16SrcDir)/%.c, $(bf16FNames))
bf16Obj = $(patsubst %, $(bf16ObjDir)/%.o, $(bf16FNames))
p16Src = $(patsubst %, $(p16SrcDir)/%.cpp, $(p16FNames))
p16Obj = $(patsubst %, $(p16ObjDir)/%.o, $(p16FNames))
floatSrc = $(patsubst %, $(floatSrcDir)/%.cpp, $(floatFNames))
floatObj = $(patsubst %, $(floatObjDir)/%.o, $(floatFNames))

all: $(libDir)/bfloat16MathLib.a $(libDir)/posit16MathLib.a $(libDir)/floatMathLib.a

$(bf16ObjDir)/%.o: $(bf16SrcDir)/%.cpp
	@mkdir -p $(bf16ObjDir)
	$(CXX) -std=c++11 -O3 -c $^ -Iinclude/ -Ifunctiongen/bfloat16/full/headers -Ihelper -o $@

$(libDir)/bfloat16MathLib.a: $(bf16Obj)
	@mkdir -p $(libDir)
	ar rc $@ $^

$(p16ObjDir)/%.o: $(p16SrcDir)/%.cpp
	@mkdir -p $(p16ObjDir)
	$(CXX) -std=c++11 -O3 -c $^ -Iinclude/ -Ifunctiongen/posit16/full/headers -I$(SOFTPOSITPATH)/source/include -o $@

$(libDir)/posit16MathLib.a: $(p16Obj)
	@mkdir -p $(libDir) 
	ar rc  $@ $^ $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a 

$(floatObjDir)/%.o: $(floatSrcDir)/%.cpp
	@mkdir -p $(floatObjDir)
	$(CXX) -std=c++11 -O3 -c $^ -Iinclude/ -Ifunctiongen/float/sampling/headers -Ihelper -o $@

$(libDir)/floatMathLib.a: $(floatObj)
	@mkdir -p $(libDir)
	ar rc $@ $^

clean:
	rm -rf obj lib *.dSYM
