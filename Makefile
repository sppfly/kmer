# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror

# Source and object files
SRCS = main.cpp kmer.cpp test.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
	