#!/bin/bash

run_llvm_jit() {
    echo "run llvm jit"
    echo "compile to llvm bc"

    # 路径
    path="../src/"

    # 编译
    compile_time_start=$(date +%s%N)/1000000
    clang -emit-llvm -c "${path}main.cpp" -o main.bc -isystem /usr/include/c++/10
    clang -emit-llvm -c "${path}Structs.cpp" -o Structs.bc -isystem /usr/include/c++/9
    clang -emit-llvm -c "${path}q1.cpp" -o q1.bc -isystem /usr/include/c++/9

    # 链接
    llvm-link main.bc Structs.bc q1.bc -o combined.bc
    echo "compile time: $(($(date +%s%N)/1000000 - compile_time_start))"

    # 删除中间文件
    rm main.bc Structs.bc q1.bc
    
    # 使用orc JIT运行
    run_time_start=$(date +%s%N)/1000000
    lli --jit-kind=orc combined.bc
    echo "run time1: $(($(date +%s%N)/1000000 - run_time_start))"

    # 使用orc-lazy JIT运行
    run_time_start=$(date +%s%N)/1000000
    lli --jit-kind=orc-lazy combined.bc
    echo "run time2: $(($(date +%s%N)/1000000 - run_time_start))"
}

run_llvm_jit
