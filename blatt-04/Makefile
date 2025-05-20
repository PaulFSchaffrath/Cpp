.SUFFIXES:
.PHONY: all compile checkstyle test clean

CXX = clang++-14 -Wall -Wextra -fsanitize=address
BASENAME = GameOfLife
LIBS = -lncurses
TESTLIBS = -lgtest -lgtest_main -lpthread

all: compile checkstyle test

compile: $(BASENAME)Main 

checkstyle:
	clang-format-14 --dry-run -Werror *.h *.cpp

test: $(BASENAME)Test
	./$<

%.o: %.cpp *.h
	$(CXX) -c $<

%Main: %Main.o %.o
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o %.o
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)


clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o

format:
	clang-format-14 -i *.cpp *.h
