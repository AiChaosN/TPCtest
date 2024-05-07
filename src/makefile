# 定义编译器
CXX = clang++

# 定义编译器标志
CXXFLAGS = -Wall -std=c++20

# 定义目标可执行文件
TARGET = demo12

# 定义源文件
SRCS = Structs.cpp q12.cpp

# 默认目标
all: $(TARGET)

# 构建目标可执行文件
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) -ftime-trace

# 清理目标
clean:
	rm -f $(TARGET)

# 伪目标
.PHONY: all clean
