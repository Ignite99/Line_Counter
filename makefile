# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Sources and objects
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Executable
EXEC = $(BIN_DIR)/my_program

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the program
run: $(EXEC)
	$(EXEC)

.PHONY: all clean run