# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/mirai/projet-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mirai/projet-cpp/build

# Include any dependencies generated for this target.
include src/CMakeFiles/projet-cpp.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/projet-cpp.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/projet-cpp.dir/flags.make

src/CMakeFiles/projet-cpp.dir/main.cpp.o: src/CMakeFiles/projet-cpp.dir/flags.make
src/CMakeFiles/projet-cpp.dir/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mirai/projet-cpp/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/projet-cpp.dir/main.cpp.o"
	cd /home/mirai/projet-cpp/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/projet-cpp.dir/main.cpp.o -c /home/mirai/projet-cpp/src/main.cpp

src/CMakeFiles/projet-cpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/projet-cpp.dir/main.cpp.i"
	cd /home/mirai/projet-cpp/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/mirai/projet-cpp/src/main.cpp > CMakeFiles/projet-cpp.dir/main.cpp.i

src/CMakeFiles/projet-cpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/projet-cpp.dir/main.cpp.s"
	cd /home/mirai/projet-cpp/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/mirai/projet-cpp/src/main.cpp -o CMakeFiles/projet-cpp.dir/main.cpp.s

src/CMakeFiles/projet-cpp.dir/main.cpp.o.requires:
.PHONY : src/CMakeFiles/projet-cpp.dir/main.cpp.o.requires

src/CMakeFiles/projet-cpp.dir/main.cpp.o.provides: src/CMakeFiles/projet-cpp.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/projet-cpp.dir/build.make src/CMakeFiles/projet-cpp.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/projet-cpp.dir/main.cpp.o.provides

src/CMakeFiles/projet-cpp.dir/main.cpp.o.provides.build: src/CMakeFiles/projet-cpp.dir/main.cpp.o

# Object files for target projet-cpp
projet__cpp_OBJECTS = \
"CMakeFiles/projet-cpp.dir/main.cpp.o"

# External object files for target projet-cpp
projet__cpp_EXTERNAL_OBJECTS =

projet-cpp: src/CMakeFiles/projet-cpp.dir/main.cpp.o
projet-cpp: src/CMakeFiles/projet-cpp.dir/build.make
projet-cpp: src/CMakeFiles/projet-cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../projet-cpp"
	cd /home/mirai/projet-cpp/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/projet-cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/projet-cpp.dir/build: projet-cpp
.PHONY : src/CMakeFiles/projet-cpp.dir/build

src/CMakeFiles/projet-cpp.dir/requires: src/CMakeFiles/projet-cpp.dir/main.cpp.o.requires
.PHONY : src/CMakeFiles/projet-cpp.dir/requires

src/CMakeFiles/projet-cpp.dir/clean:
	cd /home/mirai/projet-cpp/build/src && $(CMAKE_COMMAND) -P CMakeFiles/projet-cpp.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/projet-cpp.dir/clean

src/CMakeFiles/projet-cpp.dir/depend:
	cd /home/mirai/projet-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mirai/projet-cpp /home/mirai/projet-cpp/src /home/mirai/projet-cpp/build /home/mirai/projet-cpp/build/src /home/mirai/projet-cpp/build/src/CMakeFiles/projet-cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/projet-cpp.dir/depend
