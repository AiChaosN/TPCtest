#!/bin/bash

# 设置编译器，使用clang++
COMPILER=clang++

# 设置包含的头文件目录
INCLUDE_DIR="."

# 输出目录
OUTPUT_DIR="../bitcode"

# 确保输出目录存在
mkdir -p $OUTPUT_DIR

# 单独编译Structs.cpp为bitcode
$COMPILER -std=c++17 -I $INCLUDE_DIR -emit-llvm -c Structs.cpp -o "$OUTPUT_DIR/Structs.bc"

# 从src目录编译所有q开头的cpp文件为LLVM bitcode
for file in q*.cpp; do
    # 获取不带后缀的文件名，剔除路径部分
    base_name=$(basename "$file" .cpp)
    
    # 单独编译每个q*.cpp文件为LLVM bitcode
    $COMPILER -std=c++17 -I $INCLUDE_DIR -emit-llvm -c $file -o "$OUTPUT_DIR/$base_name.bc"
    
    # 链接Structs.bc与当前生成的bitcode文件
    llvm-link "$OUTPUT_DIR/Structs.bc" "$OUTPUT_DIR/$base_name.bc" -o "$OUTPUT_DIR/$base_name.bc"
done

echo "Bitcode compilation complete."
