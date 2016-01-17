# Object declarations
WARNINGSFLAGS = -std=c++11 -Wall -Wextra
SKIP_LINKER = -c

########################################################
all: IntMatrix tar

tar:
	tar cvf ex1.tar IntMatrixDriver.cpp IntMatrix.h IntMatrix.cpp Makefile

IntMatrix: IntMatrixDriver.o IntMatrix.o
	$(CXX) $(WARNINGSFLAGS) IntMatrixDriver.o IntMatrix.o -o  IntMatrixMainDriver

IntMatrixDriver.o: IntMatrixDriver.cpp IntMatrix.h
	$(CXX) $(SKIP_LINKER) $(WARNINGSFLAGS) IntMatrixDriver.cpp

IntMatrix.o: IntMatrix.cpp IntMatrix.h
	$(CXX) $(SKIP_LINKER) $(WARNINGSFLAGS) IntMatrix.cpp

clean:
	rm -f IntMatrixDriver *.o ex1.tar

.PHONY: all clean tar
