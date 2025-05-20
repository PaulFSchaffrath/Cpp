.SUFFIXES:
.PRECIOUS: %.o
.PHONY: all compile checkstyle test clean

CXX = clang++-14 -Wall -Wextra -Wdeprecated -fsanitize=address
MAIN_BINARY = $(basename $(wildcard *Main.cpp))
TEST_BINARY = $(basename $(wildcard *Test.cpp))
LIBS = -lncurses
TESTLIBS = -lgtest -lgtest_main -lpthread
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard *.cpp))))

all: compile checkstyle test

compile: $(MAIN_BINARY) $(TEST_BINARY)

checkstyle:
	clang-format-14 --dry-run -Werror *.h *.cpp

test: $(TEST_BINARY)
	./$<

%.o: %.cpp *.h
	$(CXX) -c $<

%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o

format:
	clang-format-14 -i *.cpp *.h
