compile:
	clang++ -o GcdMain GcdMain.cpp 
	clang++ -o GcdTest GcdTest.cpp -lgtest

test:
	./GcdTest

checkstyle:
	clang-format-14 *.cpp --dry-run -Werror

clean:
	rm -f ./GcdMain ./GcdTest

format:
	clang-format-14 -i *.cpp
