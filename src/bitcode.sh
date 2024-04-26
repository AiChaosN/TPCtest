#!/bin/bash

# init compiler and optimize level
COMPILER=clang++
Optimize_level=-O3

# Path
INCLUDE_DIR="."
OUTPUT_DIR="../bitcode"

# make sure output directory exists
mkdir -p $OUTPUT_DIR

# compile Structs.cpp to LLVM bitcode
$COMPILER -std=c++17 -I $INCLUDE_DIR -emit-llvm -c Structs.cpp -o "$OUTPUT_DIR/Structs.bc"

# compile q*.cpp to LLVM bitcode
for file in q*.cpp; do
    base_name=$(basename "$file" .cpp)
    
    # compile each q*.cpp to bitcode
    start_time=$(date +%s%N)/1000000
    $COMPILER -std=c++17 -I $INCLUDE_DIR -emit-llvm -c $file $Optimize_level -o "$OUTPUT_DIR/$base_name.bc"
    
    # link Structs.bc to q*.bc
    llvm-link "$OUTPUT_DIR/Structs.bc" "$OUTPUT_DIR/$base_name.bc" -o "$OUTPUT_DIR/$base_name.bc"
    echo "$base_name compile to .bc, time: $(($(date +%s%N)/1000000 - start_time))"
done

echo "Bitcode compilation by $COMPILER complete."
