#!/bin/bash


# init compiler and optimize level
COMPILER=g++
if [ "$1" == "clang" ]; then
    COMPILER=clang++
fi
Optimize_level=-O3

# Path
# include directory
INCLUDE_DIR="./include"
# output directory
OUTPUT_DIR="../bin"

# make sure output directory exists
mkdir -p $OUTPUT_DIR

# compile Structs.cpp to exe
for file in q*.cpp; do
    # get file name without suffix, remove path part
    base_name=$(basename "$file" .cpp)
    
    # compile each q*.cpp to exe
    start_time=$(date +%s%N)/1000000
    $COMPILER -std=c++17 -I $INCLUDE_DIR $Optimize_level -o "$OUTPUT_DIR/$base_name" $file Structs.cpp || exit 1
    echo "$base_name compile to exe end, time: $(($(date +%s%N)/1000000 - start_time))"

done

echo "Compilation by $COMPILER complete."

