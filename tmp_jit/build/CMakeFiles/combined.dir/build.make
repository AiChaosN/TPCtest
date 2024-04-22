# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aichaos/mylab/9992/TPCtest/tmp_jit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aichaos/mylab/9992/TPCtest/tmp_jit/build

# Utility rule file for combined.

# Include the progress variables for this target.
include CMakeFiles/combined.dir/progress.make

CMakeFiles/combined: main.bc
CMakeFiles/combined: Structs.bc
CMakeFiles/combined: q1.bc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/aichaos/mylab/9992/TPCtest/tmp_jit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "All IR files are prepared."

main.bc: ../../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/aichaos/mylab/9992/TPCtest/tmp_jit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Compiling ../src/main.cpp to LLVM IR"
	clang++ -emit-llvm -c /home/aichaos/mylab/9992/TPCtest/tmp_jit/../src/main.cpp -o main.bc

Structs.bc: ../../src/Structs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/aichaos/mylab/9992/TPCtest/tmp_jit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Compiling ../src/Structs.cpp to LLVM IR"
	clang++ -emit-llvm -c /home/aichaos/mylab/9992/TPCtest/tmp_jit/../src/Structs.cpp -o Structs.bc

q1.bc: ../../src/q1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/aichaos/mylab/9992/TPCtest/tmp_jit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Compiling ../src/q1.cpp to LLVM IR"
	clang++ -emit-llvm -c /home/aichaos/mylab/9992/TPCtest/tmp_jit/../src/q1.cpp -o q1.bc

combined: CMakeFiles/combined
combined: main.bc
combined: Structs.bc
combined: q1.bc
combined: CMakeFiles/combined.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Linking all IR files into combined-final.bc"
	llvm-link -o query.bc main.bc Structs.bc q1.bc
.PHONY : combined

# Rule to build all files generated by this target.
CMakeFiles/combined.dir/build: combined

.PHONY : CMakeFiles/combined.dir/build

CMakeFiles/combined.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/combined.dir/cmake_clean.cmake
.PHONY : CMakeFiles/combined.dir/clean

CMakeFiles/combined.dir/depend:
	cd /home/aichaos/mylab/9992/TPCtest/tmp_jit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aichaos/mylab/9992/TPCtest/tmp_jit /home/aichaos/mylab/9992/TPCtest/tmp_jit /home/aichaos/mylab/9992/TPCtest/tmp_jit/build /home/aichaos/mylab/9992/TPCtest/tmp_jit/build /home/aichaos/mylab/9992/TPCtest/tmp_jit/build/CMakeFiles/combined.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/combined.dir/depend

