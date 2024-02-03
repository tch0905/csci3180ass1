# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target executable name
TARGET = executable_name

# Source files
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Header files
HDRS = $(wildcard *.h)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)