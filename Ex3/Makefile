CPPFLAGS=-std=c++11 -pthread -Wall -Wextra -Wvla -O

TARNAME=ex3.tar
TARFILES=Matrix.hpp Makefile README

.SUFFIXES:

Matrix: Matrix.hpp.gch

Matrix.hpp.gch: Matrix.hpp
	$(CXX) $(CPPFLAGS) -x c++-header Matrix.hpp

tar:
	tar cvf $(TARNAME) $(TARFILES)

clean:
	rm -rf *.gch $(TARNAME)

.PHONY: clean
	
.DEFAULT_GOAL := Matrix.hpp.gch