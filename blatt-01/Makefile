all: checkstyle compile test clean


compile:
	clang++ -o GcdMain GcdMain.cpp
	clang++ -std=c++14 -o GcdTest GcdTest.cpp -lgtest

format:
	clang-format -i Gcd.cpp
	clang-format -i GcdMain.cpp
	clang-format -i GcdTest.cpp

checkstyle:
	clang-format --dry-run -Werror *.cpp

test:
	./GcdTest

clean:
	rm -f GcdMain
	rm -f GcdTest
