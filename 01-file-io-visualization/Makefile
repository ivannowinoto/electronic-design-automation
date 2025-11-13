# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Source files
SRC = main.cpp genPlot.cpp
OBJ = $(SRC:.cpp=.o)

# Output executable
TARGET = genPlot

# Default rule
all: $(TARGET)

# Link objects into executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp genPlot.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)

