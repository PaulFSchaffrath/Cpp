.SUFFIXES:
.PRECIOUS: %.o
.PHONY: all compile checkstyle test clean

CXX = clang++ -std=c++20 -Wall -Wextra -Wdeprecated -fsanitize=address
MAIN_BINARY = $(basename $(wildcard *Main.cpp))
TEST_BINARY = $(basename $(wildcard *Test.cpp))
LIBS = -lncurses
TESTLIBS = -lgtest -lgtest_main -lpthread
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard *.cpp))))

all: compile checkstyle test # run

compile: $(MAIN_BINARY) $(TEST_BINARY)

checkstyle:
	clang-format --dry-run -Werror *.h *.cpp

test: $(TEST_BINARY)
	./$<

run: $(MAIN_BINARY)
	reset
	./$< 4500

%.o: %.cpp *.h
	$(CXX) -c -g $<

%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o

format:
	clang-format -i *.cpp *.h
