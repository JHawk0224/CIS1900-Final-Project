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
include TermOx/demos/CMakeFiles/readme.demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include TermOx/demos/CMakeFiles/readme.demo.dir/compiler_depend.make

# Include the progress variables for this target.
include TermOx/demos/CMakeFiles/readme.demo.dir/progress.make

# Include the compile flags for this target's objects.
include TermOx/demos/CMakeFiles/readme.demo.dir/flags.make

TermOx/demos/CMakeFiles/readme.demo.dir/readme.main.cpp.o: TermOx/demos/CMakeFiles/readme.demo.dir/flags.make
TermOx/demos/CMakeFiles/readme.demo.dir/readme.main.cpp.o: TermOx/demos/readme.main.cpp
TermOx/demos/CMakeFiles/readme.demo.dir/readme.main.cpp.o: TermOx/demos/CMakeFiles/readme.demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TermOx/demos/CMakeFiles/readme.demo.dir/readme.main.cpp.o"
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos" && /opt/homebrew/bin/g++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT TermOx/demos/CMakeFiles/readme.demo.dir/readme.main.cpp.o -MF CMakeFiles/readme.demo.dir/readme.main.cpp.o.d -o CMakeFiles/readme.demo.dir/readme.main.cpp.o -c "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos/readme.main.cpp"

TermOx/demos/CMakeFiles/readme.demo.dir/readme.main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readme.demo.dir/readme.main.cpp.i"
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos" && /opt/homebrew/bin/g++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos/readme.main.cpp" > CMakeFiles/readme.demo.dir/readme.main.cpp.i

TermOx/demos/CMakeFiles/readme.demo.dir/readme.main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readme.demo.dir/readme.main.cpp.s"
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos" && /opt/homebrew/bin/g++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos/readme.main.cpp" -o CMakeFiles/readme.demo.dir/readme.main.cpp.s

# Object files for target readme.demo
readme_demo_OBJECTS = \
"CMakeFiles/readme.demo.dir/readme.main.cpp.o"

# External object files for target readme.demo
readme_demo_EXTERNAL_OBJECTS =

TermOx/demos/readme.demo: TermOx/demos/CMakeFiles/readme.demo.dir/readme.main.cpp.o
TermOx/demos/readme.demo: TermOx/demos/CMakeFiles/readme.demo.dir/build.make
TermOx/demos/readme.demo: TermOx/src/libTermOx.a
TermOx/demos/readme.demo: TermOx/external/Escape/libescape.a
TermOx/demos/readme.demo: TermOx/demos/CMakeFiles/readme.demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable readme.demo"
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readme.demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TermOx/demos/CMakeFiles/readme.demo.dir/build: TermOx/demos/readme.demo
.PHONY : TermOx/demos/CMakeFiles/readme.demo.dir/build

TermOx/demos/CMakeFiles/readme.demo.dir/clean:
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos" && $(CMAKE_COMMAND) -P CMakeFiles/readme.demo.dir/cmake_clean.cmake
.PHONY : TermOx/demos/CMakeFiles/readme.demo.dir/clean

TermOx/demos/CMakeFiles/readme.demo.dir/depend:
	cd "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/jhawk/Desktop/CIS 190/Personal/CIS1900-Final-Project" "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos" "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project" "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos" "/Users/jhawk/desktop/CIS 190/Personal/CIS1900-Final-Project/TermOx/demos/CMakeFiles/readme.demo.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : TermOx/demos/CMakeFiles/readme.demo.dir/depend
