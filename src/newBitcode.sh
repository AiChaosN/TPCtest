#!/bin/bash

# 初始化编译器和优化级别
COMPILER=clang++
Optimize_level=-O3

# 路径
INCLUDE_DIR="."
OUTPUT_DIR="../bitcode"

# 确保输出目录存在
mkdir -p $OUTPUT_DIR

# 编译 Structs.cpp 到 LLVM bitcode
$COMPILER -std=c++17 -I $INCLUDE_DIR -emit-llvm -c Structs.cpp -o "$OUTPUT_DIR/Structs.bc" || exit 1

# 编译 q*.cpp 到 LLVM bitcode
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
    
    # 编译 q*.cpp 到 bitcode
    start_time=$(date +%s%N)/1000000
    $COMPILER -std=c++17 -I $INCLUDE_DIR -emit-llvm -c $file $Optimize_level -o "$OUTPUT_DIR/$base_name.bc" || exit 1
    compile_time=$(($(date +%s%N)/1000000 - start_time))
    
    # 链接 Structs.bc 和 q*.bc
    start_time=$(date +%s%N)/1000000
    llvm-link "$OUTPUT_DIR/Structs.bc" "$OUTPUT_DIR/$base_name.bc" -o "$OUTPUT_DIR/${base_name}_linked.bc" || exit 1
    link_time=$(($(date +%s%N)/1000000 - start_time))
    
    total_time=$((compile_time + link_time))
    echo "$base_name compile to .bc, compile time: ${compile_time} ms, link time: ${link_time} ms, total time: ${total_time} ms"
done

echo "Bitcode compilation by $COMPILER complete."
