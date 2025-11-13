# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++17

# Source Files
SRCS = main.cpp io.cpp legalizer.cpp

# Header Files
HDRS = legalizer.h

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Output Executable
TARGET = legalizer

# Default Target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp to .o
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

