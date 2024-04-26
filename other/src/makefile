# 定义编译器
CXX = g++

# 定义编译器标志
CXXFLAGS = -Wall -std=c++20

# 定义目标可执行文件
TARGET = demo

# 定义源文件
SRCS = main.cpp  Structs.cpp q1.cpp q3.cpp q5.cpp q7.cpp q9.cpp q11.cpp q13.cpp q17.cpp q19.cpp q21.cpp

# 默认目标
all: $(TARGET)

# 构建目标可执行文件
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# 清理目标
clean:
	rm -f $(TARGET)

# 伪目标
.PHONY: all clean
