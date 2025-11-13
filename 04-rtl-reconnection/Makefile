# Compiler settings
CXX       := g++
CXXFLAGS  := -std=c++11 -Wall -Wextra -O2

# Source and object files
SOURCES   := main.cpp io.cpp RTL.cpp
HEADERS   := RTL.h
OBJECTS   := $(SOURCES:.cpp=.o)

# Name of the final executable
TARGET    := rtl_reconnect

.PHONY: all clean

all: $(TARGET)

# Link step
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Compile step (one rule covers all .cpp files)
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

