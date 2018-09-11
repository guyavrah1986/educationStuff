# Minimum CMake required
cmake_minimum_required(VERSION 3.10)

# Project
project(myCatchBasicExample)

message(STATUS "proccessing CMakeLists.txt file within:${CMAKE_CURRENT_LIST_DIR}")

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# Add the source files into a list
set(BASIC_CATCH_EXAMPLE_SRC main.cpp
							catch.hpp
							simpleObj.h
							simpleObj.cpp)

#Executable setup
set(executable_name basicProtobufExample_cpp)
add_executable(myCatchExampleExe ${BASIC_CATCH_EXAMPLE_SRC})
