CXXFLAGS = -std=c++11
COMPILE = g++ $(CXXFLAGS) -c


main: biaMachineCode.o
	g++ $(CXXFLAGS) -o main main.cpp biaMachineCode.o

biaMachineCode.o: biaMachineCode.h biaMachineCode.cpp \
	biaMachineContext.h
	$(COMPILE) biaMachineCode.cpp

clean:
	rm -f *.o main