.SUFFIXES:
.PHONY: clean format checkstyle compile run test
.PRECIOUS: %.o

CXX = clang++ -std=c++14
HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECT = Snake.o
MAIN = SnakeMain
TEST = SnakeTest

all: clean format checkstyle compile run test

compile: $(MAIN) $(TEST)

run:
	./$(MAIN)

format:
	clang-format -i $(SOURCES)

checkstyle:
	clang-format --dry-run -Werror $(SOURCES)

test:
	./$(TEST)

clean:
	rm -f $(MAIN)
	rm -f $(TEST)
	rm -f *.o
	rm -f a.out

%.o: %.cpp $(HEADER)
	$(CXX) -c $<

$(MAIN): SnakeMain.o $(OBJECT)
	$(CXX) -o $@ $^ -lncurses

$(TEST): SnakeTest.o $(OBJECT)
	$(CXX) -o $@ $^ -lncurses -lgtest -lgtest_main

