# 定义编译器
CXX = g++

# 定义编译选项
CXXFLAGS = -Wall -g

# 目标可执行文件
TARGET = demo

# 构建目标的规则
$(TARGET): demo.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) demo.o

# 编译源文件的规则
demo.o: demo.cpp
	$(CXX) $(CXXFLAGS) -c demo.cpp

# 清理编译生成的文件
clean:
	rm -f $(TARGET) demo.o
