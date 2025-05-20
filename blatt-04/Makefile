.SUFFIXES:
.PHONY: clean format checkstyle compile run  # test
.PRECIOUS: %.o

CXX = clang++ -std=c++14
HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECT = GameOfLife.o
MAIN = GameOfLifeMain
TEST = GameOfLifeTest

all: clean format checkstyle compile run  # test

compile: $(MAIN)  # $(TEST)

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

$(MAIN): GameOfLifeMain.o $(OBJECT)
	$(CXX) -o $@ $^ -lncurses

# $(TEST): GameOfLifeTest.o $(OBJECT)
#	$(CXX) -o $@ $^ -lncurses -lgtest -lgtest_main

