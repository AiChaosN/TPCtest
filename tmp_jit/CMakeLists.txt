cmake_minimum_required(VERSION 3.10)
project(LLVMJITExample)

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定使用 Clang 编译器
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# 设置源文件
set(SOURCE_FILES "../src/main.cpp" "../src/Structs.cpp" "../src/q1.cpp")

# 为每个源文件添加一个目标，生成 LLVM IR
foreach(SOURCE_FILE ${SOURCE_FILES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    set(OUTPUT_FILE "${FILE_NAME}.bc")
    add_custom_command(
        OUTPUT ${OUTPUT_FILE}
        COMMAND ${CMAKE_CXX_COMPILER} -emit-llvm -c ${CMAKE_SOURCE_DIR}/${SOURCE_FILE} -o ${OUTPUT_FILE}
        DEPENDS ${SOURCE_FILE}
        COMMENT "Compiling ${SOURCE_FILE} to LLVM IR"
    )
    list(APPEND IR_FILES ${OUTPUT_FILE})
endforeach()

# 添加一个目标，依赖于所有生成的 LLVM IR 文件
add_custom_target(combined ALL
    DEPENDS ${IR_FILES}
    COMMENT "All IR files are prepared."
)

# 添加一个命令，在所有 IR 文件生成后，使用 llvm-link 合并它们
add_custom_command(
    TARGET combined
    POST_BUILD
    COMMAND llvm-link -o query.bc ${IR_FILES}
    COMMENT "Linking all IR files into combined-final.bc"
)
