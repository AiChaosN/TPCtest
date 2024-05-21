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
# 对象文件目录
OBJ_DIR="./obj"

# 确保输出目录和对象文件目录存在
mkdir -p $OUTPUT_DIR
mkdir -p $OBJ_DIR

# 编译 Structs.cpp 到对象文件
$COMPILER -std=c++17 -I $INCLUDE_DIR $Optimize_level -c Structs.cpp -o $OBJ_DIR/Structs.o || exit 1

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
    
    # 编译 q*.cpp 到对象文件
    start_time=$(date +%s%N)/1000000
    $COMPILER -std=c++17 -I $INCLUDE_DIR $Optimize_level -c $file -o $OBJ_DIR/$base_name.o || exit 1
    compile_time=$(($(date +%s%N)/1000000 - start_time))
    
    # 链接对象文件到可执行文件
    start_time=$(date +%s%N)/1000000
    $COMPILER $Optimize_level -o "$OUTPUT_DIR/$base_name" $OBJ_DIR/$base_name.o $OBJ_DIR/Structs.o || exit 1
    link_time=$(($(date +%s%N)/1000000 - start_time))
    
    total_time=$((compile_time + link_time))
    echo "$base_name compile and link end, compile time: ${compile_time} ms, link time: ${link_time} ms, total time: ${total_time} ms"
done

echo "Compilation by $COMPILER complete."
