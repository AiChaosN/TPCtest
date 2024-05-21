#!/bin/bash

# 初始化编译器和优化级别
COMPILER=clang++
Optimize_level=-O3

# 路径
INCLUDE_DIR="."
OUTPUT_DIR="../bitcode"

# 确保输出目录存在
mkdir -p $OUTPUT_DIR

# 按顺序编译 q1.cpp 到 q22.cpp 到 LLVM bitcode
for i in {1..22}; do
    file="q${i}.cpp"
    
    # 检查文件是否存在
    if [ ! -f "$file" ]; then
        echo "File $file does not exist, skipping..."
        continue
    fi
    
    base_name=$(basename "$file" .cpp)
    
    # 编译每个 q*.cpp 和 Structs.cpp 一起到 bitcode
    start_time=$(date +%s%N)/1000000
    $COMPILER -std=c++17 -I $INCLUDE_DIR -emit-llvm $Optimize_level -o "$OUTPUT_DIR/$base_name.bc" $file Structs.cpp || exit 1
    compile_link_time=$(($(date +%s%N)/1000000 - start_time))
    
    echo "$base_name compile and link to .bc, time: ${compile_link_time} ms"
done

echo "Bitcode compilation by $COMPILER complete."
