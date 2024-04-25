# make

# ./demo > ../test/sql_ans/cpp_ans.txt

#!/bin/bash

# 设置编译器
COMPILER=g++

# 设置包含的头文件目录
INCLUDE_DIR="./include"

# 输出目录
OUTPUT_DIR="../bin"

# 确保输出目录存在
mkdir -p $OUTPUT_DIR

# 从src目录编译所有q开头的cpp文件
for file in q*.cpp; do
    # 获取不带后缀的文件名，剔除路径部分
    base_name=$(basename "$file" .cpp)
    
    # 编译cpp文件，启用C++17标准，生成可执行文件，输出到指定目录
    $COMPILER -std=c++17 -I $INCLUDE_DIR -o "$OUTPUT_DIR/$base_name" $file Structs.cpp || exit 1

done

echo "Compilation complete."

