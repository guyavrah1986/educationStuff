# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/guy/Desktop/Guy/Dev/http-server/unitTests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guy/Desktop/Guy/Dev/http-server/unitTests

# Include any dependencies generated for this target.
include googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/depend.make

# Include the progress variables for this target.
include googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/progress.make

# Include the compile flags for this target's objects.
include googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/flags.make

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/flags.make
googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o: googletest-release-1.8.0/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guy/Desktop/Guy/Dev/http-server/unitTests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o -c /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googletest/src/gtest-all.cc

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.i"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googletest/src/gtest-all.cc > CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.i

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.s"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googletest/src/gtest-all.cc -o CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.s

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.requires:

.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.requires

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.provides: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.requires
	$(MAKE) -f googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/build.make googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.provides.build
.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.provides

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.provides.build: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o


googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/flags.make
googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o: googletest-release-1.8.0/googlemock/src/gmock-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guy/Desktop/Guy/Dev/http-server/unitTests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/src/gmock-all.cc.o -c /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock/src/gmock-all.cc

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/src/gmock-all.cc.i"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock/src/gmock-all.cc > CMakeFiles/gmock_main.dir/src/gmock-all.cc.i

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/src/gmock-all.cc.s"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock/src/gmock-all.cc -o CMakeFiles/gmock_main.dir/src/gmock-all.cc.s

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires:

.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires
	$(MAKE) -f googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/build.make googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides.build
.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides.build: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o


googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/flags.make
googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: googletest-release-1.8.0/googlemock/src/gmock_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guy/Desktop/Guy/Dev/http-server/unitTests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.o -c /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock/src/gmock_main.cc

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/src/gmock_main.cc.i"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock/src/gmock_main.cc > CMakeFiles/gmock_main.dir/src/gmock_main.cc.i

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/src/gmock_main.cc.s"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock/src/gmock_main.cc -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.s

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires:

.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires
	$(MAKE) -f googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/build.make googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides.build
.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides.build: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o


# Object files for target gmock_main
gmock_main_OBJECTS = \
"CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o" \
"CMakeFiles/gmock_main.dir/src/gmock-all.cc.o" \
"CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"

# External object files for target gmock_main
gmock_main_EXTERNAL_OBJECTS =

googletest-release-1.8.0/googlemock/libgmock_main.a: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o
googletest-release-1.8.0/googlemock/libgmock_main.a: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o
googletest-release-1.8.0/googlemock/libgmock_main.a: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
googletest-release-1.8.0/googlemock/libgmock_main.a: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/build.make
googletest-release-1.8.0/googlemock/libgmock_main.a: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/guy/Desktop/Guy/Dev/http-server/unitTests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libgmock_main.a"
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean_target.cmake
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/build: googletest-release-1.8.0/googlemock/libgmock_main.a

.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/build

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/requires: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.requires
googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/requires: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires
googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/requires: googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires

.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/requires

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/clean:
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean.cmake
.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/clean

googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/depend:
	cd /home/guy/Desktop/Guy/Dev/http-server/unitTests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guy/Desktop/Guy/Dev/http-server/unitTests /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock /home/guy/Desktop/Guy/Dev/http-server/unitTests /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock /home/guy/Desktop/Guy/Dev/http-server/unitTests/googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : googletest-release-1.8.0/googlemock/CMakeFiles/gmock_main.dir/depend

