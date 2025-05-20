.SUFFIXES:
.PHONY: all compile checkstyle test clean

all: clean compile test checkstyle
compile: GcdMain 

Gcd.o: Gcd.cpp Gcd.h
	clang++ -c Gcd.cpp

GcdMain.o: GcdMain.cpp Gcd.h
	clang++ -c GcdMain.cpp

GcdTest.o: GcdTest.cpp Gcd.h
	clang++ -c GcdTest.cpp

GcdMain: Gcd.o GcdMain.o
	clang++ -o GcdMain GcdMain.o Gcd.o 

GcdTest: Gcd.o GcdTest.o
	clang++ -o GcdTest GcdTest.o Gcd.o -lgtest -lpthread

test: GcdTest
	./GcdTest

checkstyle:
	clang-format-14 *.cpp --dry-run -Werror

clean:
	rm -f ./GcdMain ./GcdTest *.o

format:
	clang-format-14 -i *.cpp
