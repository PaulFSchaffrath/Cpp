.PHONY: all compile checkstyle test clean
.SUFFIXES:
.PRECIOUS: %.o


all: checkstyle compile test clean

GcdMain: Gcd.o GcdMain.o
	clang++ -o GcdMain Gcd.o GcdMain.o

GcdTest: Gcd.o GcdTest.o
	clang++ -o GcdTest Gcd.o GcdTest.o -lgtest

Gcd.o: Gcd.cpp
	clang++ -c ./Gcd.cpp

GcdMain.o: GcdMain.cpp
	clang++ -c ./GcdMain.cpp

GcdTest.o: GcdTest.cpp
	clang++ -std=c++14 -c ./GcdTest.cpp

compile: GcdMain GcdTest

format:
	clang-format -i Gcd.cpp
	clang-format -i GcdMain.cpp
	clang-format -i GcdTest.cpp

checkstyle:
	clang-format --dry-run -Werror *.cpp

test:
	./GcdTest

clean:
	rm -f ./GcdMain
	rm -f ./GcdTest
	rm -f ./*.o
