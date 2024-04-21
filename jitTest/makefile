
CXX = llvm

CXXFLAGS = -Wall -std=c++20

TARGET = jitTest

SRCS = *.cpp src/*.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean