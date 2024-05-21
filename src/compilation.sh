#!/bin/bash

# ./compilation.sh clang
# ./compilation.sh g++

# 初始化编译器和优化级别
COMPILER=g++
if [ "$1" == "clang" ]; then
    COMPILER=clang++
fi
Optimize_level=-O3

# 路径
# 包含目录
INCLUDE_DIR="./include"
# 输出目录
OUTPUT_DIR="../bin"

# 确保输出目录存在
mkdir -p $OUTPUT_DIR

# 按顺序编译 q1.cpp 到 q22.cpp
for i in {1..22}; do
    # 生成文件名
    file="q${i}.cpp"
    
    # 检查文件是否存在
    if [ ! -f "$file" ]; then
        echo "File $file does not exist, skipping..."
        continue
    fi
    
    # 获取不带后缀的文件名
    base_name=$(basename "$file" .cpp)
    
    # 编译每个 q*.cpp 到可执行文件
    start_time=$(date +%s%N)/1000000
    $COMPILER -std=c++17 -I $INCLUDE_DIR $Optimize_level -o "$OUTPUT_DIR/$base_name" $file Structs.cpp || exit 1
    echo "$base_name compile to exe end, time: $(($(date +%s%N)/1000000 - start_time)) ms"
done

echo "Compilation by $COMPILER complete."
