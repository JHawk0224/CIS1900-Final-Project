# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/jhawk/Desktop/CIS 190/Personal/CIS1900-Final-Project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project"

# Include any dependencies generated for this target.
include TermOx/tests/CMakeFiles/passive.ui.test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include TermOx/tests/CMakeFiles/passive.ui.test.dir/compiler_depend.make

# Include the progress variables for this target.
include TermOx/tests/CMakeFiles/passive.ui.test.dir/progress.make

# Include the compile flags for this target's objects.
include TermOx/tests/CMakeFiles/passive.ui.test.dir/flags.make

TermOx/tests/CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o: TermOx/tests/CMakeFiles/passive.ui.test.dir/flags.make
TermOx/tests/CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o: TermOx/tests/passive.ui.test.cpp
TermOx/tests/CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o: TermOx/tests/CMakeFiles/passive.ui.test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TermOx/tests/CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o"
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests" && /opt/homebrew/bin/g++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT TermOx/tests/CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o -MF CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o.d -o CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o -c "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests/passive.ui.test.cpp"

TermOx/tests/CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.i"
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests" && /opt/homebrew/bin/g++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests/passive.ui.test.cpp" > CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.i

TermOx/tests/CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.s"
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests" && /opt/homebrew/bin/g++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests/passive.ui.test.cpp" -o CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.s

# Object files for target passive.ui.test
passive_ui_test_OBJECTS = \
"CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o"

# External object files for target passive.ui.test
passive_ui_test_EXTERNAL_OBJECTS =

TermOx/tests/passive.ui.test: TermOx/tests/CMakeFiles/passive.ui.test.dir/passive.ui.test.cpp.o
TermOx/tests/passive.ui.test: TermOx/tests/CMakeFiles/passive.ui.test.dir/build.make
TermOx/tests/passive.ui.test: TermOx/src/libTermOx.a
TermOx/tests/passive.ui.test: TermOx/external/Escape/libescape.a
TermOx/tests/passive.ui.test: TermOx/tests/CMakeFiles/passive.ui.test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable passive.ui.test"
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/passive.ui.test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TermOx/tests/CMakeFiles/passive.ui.test.dir/build: TermOx/tests/passive.ui.test
.PHONY : TermOx/tests/CMakeFiles/passive.ui.test.dir/build

TermOx/tests/CMakeFiles/passive.ui.test.dir/clean:
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests" && $(CMAKE_COMMAND) -P CMakeFiles/passive.ui.test.dir/cmake_clean.cmake
.PHONY : TermOx/tests/CMakeFiles/passive.ui.test.dir/clean

TermOx/tests/CMakeFiles/passive.ui.test.dir/depend:
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/jhawk/Desktop/CIS 190/Personal/CIS1900-Final-Project" "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests" "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project" "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests" "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/tests/CMakeFiles/passive.ui.test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : TermOx/tests/CMakeFiles/passive.ui.test.dir/depend

