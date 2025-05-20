.SUFFIXES:
.PHONY: all compile checkstyle clean
.PRECIOUS: %.o

CXX = clang++ -std=c++14 -Wall -Wextra -fsanitize=address
BASENAME = GameOfLife
LIBS = -lncurses
OBJS = GameOfLife.o TerminalManager.o
TESTLIBS = -lgtest -lgtest_main -lpthread
SOURCES = $(wildcard *.cpp)

all: compile checkstyle run

run:
	./"GameOfLifeMain"

compile: $(BASENAME)Main 

checkstyle:
	clang-format --dry-run -Werror *.h *.cpp

# test: $(BASENAME)Test
# 	./$<

%.o: %.cpp *.h
	$(CXX) -c $<

%Main: %Main.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

# %Test: %Test.o $(OBJS)
# 	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o

clean+:
	rm -f *Main
	rm -f *Test
	rm -f *.o
	reset
	make

format:
	clang-format -i *.cpp *.h