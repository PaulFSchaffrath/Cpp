.SUFFIXES:
.PRECIOUS: %.o
.PHONY: all compile checkstyle test clean format run

# Compiler
CXX = clang++ -std=c++17 -Wall -Wextra -Wdeprecated -fsanitize=address

# Directories
SRC_DIR = Sources
BUILD_DIR = build
RUN_DIR = executables
HEADER_DIR = Header
MAIN_DIR = Main
TEST_DIR = Test
INCLUDE_DIRS = -I$(HEADER_DIR)

# Libraries
LIBS = -lncurses
TESTLIBS = -lgtest -lgtest_main -lpthread

# Sources and binaries
MAIN_SOURCES = $(wildcard $(MAIN_DIR)/*Main.cpp)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*Test.cpp)
MAIN_BINARY = $(RUN_DIR)/$(notdir $(basename $(MAIN_SOURCES)))
TEST_BINARY = $(RUN_DIR)/$(notdir $(basename $(TEST_SOURCES)))

# Objects
MAIN_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out $(TEST_SOURCES), $(wildcard $(SRC_DIR)/*.cpp)))
TEST_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out $(MAIN_SOURCES), $(wildcard $(SRC_DIR)/*.cpp)))

# Default target
all: compile checkstyle test

# Ensure build and run directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(RUN_DIR):
	mkdir -p $(RUN_DIR)

compile: $(BUILD_DIR) $(RUN_DIR) $(MAIN_BINARY) $(TEST_BINARY)

# Checkstyle
checkstyle:
	clang-format --dry-run -Werror $(HEADER_DIR)/*.h $(SRC_DIR)/*.cpp $(MAIN_DIR)/*.cpp $(TEST_DIR)/*.cpp

# Run the tests
test: $(TEST_BINARY)
	./$(TEST_BINARY)

# Run the main program with default keys a and d
run: $(MAIN_BINARY)
	reset
	./$(MAIN_BINARY) a d

# Compile source files into objects, ensuring the build directory exists
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(INCLUDE_DIRS) -c -g $< -o $@

$(BUILD_DIR)/%Main.o: $(MAIN_DIR)/%Main.cpp | $(BUILD_DIR)
	$(CXX) $(INCLUDE_DIRS) -c -g $< -o $@

$(BUILD_DIR)/%Test.o: $(TEST_DIR)/%Test.cpp | $(BUILD_DIR)
	$(CXX) $(INCLUDE_DIRS) -c -g $< -o $@

# Link main objects to create main binary
$(RUN_DIR)/%Main: $(BUILD_DIR)/%Main.o $(MAIN_OBJECTS) | $(RUN_DIR)
	$(CXX) -o $@ $^ $(LIBS)

# Link test objects to create test binary
$(RUN_DIR)/%Test: $(BUILD_DIR)/%Test.o $(TEST_OBJECTS) | $(RUN_DIR)
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(RUN_DIR)

format:
	clang-format -i $(HEADER_DIR)/*.h $(SRC_DIR)/*.cpp $(MAIN_DIR)/*.cpp $(TEST_DIR)/*.cpp