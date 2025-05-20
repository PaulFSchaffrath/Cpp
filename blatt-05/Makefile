.SUFFIXES:
.PHONY: all compile checkstyle test clean format

CXX = clang++ -std=c++17 -Wall -Wextra -O3 -I/usr/include/freetype2
BASENAME = GameOfLife
OBJS = $(BASENAME).o TerminalManager.o
LIBS = -lncurses 
#OBJS = $(BASENAME).o OpenGLTerminalManager.o
#LIBS = -lncurses -lglfw -lGL -lX11 -lrt -ldl -lfreetype
TESTLIBS = -lgtest -lgtest_main -lpthread

all: compile format checkstyle test

compile: $(BASENAME)Main 

checkstyle:
	clang-format-14 --dry-run -Werror *.h *.cpp

format:
	clang-format-14 -i *.h *.cpp


test: $(BASENAME)Test
	./$<

%.o: %.cpp *.h
	$(CXX) -c $<

%Main: %Main.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o
