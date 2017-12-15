CXXFLAGS = -std=c++11 -m32 -Ofast
COMPILE = g++ $(CXXFLAGS) -c


main: main.cpp biaMachineCode.o biaStreamBuffer.o \
	biaToolGcc.h
	g++ $(CXXFLAGS) -o main main.cpp biaMachineCode.o biaStreamBuffer.o

biaStreamBuffer.o: biaStreamBuffer.h biaStreamBuffer.cpp \
	biaStream.h
	$(COMPILE) biaStreamBuffer.cpp

biaMachineCode.o: biaMachineCode.h biaMachineCode.cpp \
	biaMachineContext.h
	$(COMPILE) biaMachineCode.cpp

clean:
	rm -f *.o main