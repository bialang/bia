CXXFLAGS = -std=c++11 -m32 -Ofast
COMPILE = g++ $(CXXFLAGS) -c


main: main.cpp biaMachineCode.o biaOutputStreamBuffer.o \
	biaToolGcc.hpp
	g++ $(CXXFLAGS) -o main main.cpp biaMachineCode.o biaOutputStreamBuffer.o

biaOutputStreamBuffer.o: biaOutputStreamBuffer.hpp biaOutputStreamBuffer.cpp \
	biaOutputStream.hpp
	$(COMPILE) biaOutputStreamBuffer.cpp

biaMachineCode.o: biaMachineCode.hpp biaMachineCode.cpp
	$(COMPILE) biaMachineCode.cpp

biaStorage.o: biaStorage.hpp biaStorage.cpp
	$(COMPILE) biaStorage.cpp

clean:
	rm -f *.o main