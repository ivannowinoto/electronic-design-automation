# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Output binary name
TARGET = pic_router

# Source files
SRCS = main.cpp io.cpp picRouting.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the program
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp picRouting.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the compiled program
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

