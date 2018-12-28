# ======================================================================================================================================
# general project settings
# ======================================================================================================================================
cmake_minimum_required(VERSION 3.5.1)

project(unitTestsFileSystemSqs)

message(STATUS "Processing CMakeLists.txt file in folder:${CMAKE_CURRENT_LIST_DIR}")

# ======================================================================================================================================
# GTest realted settings
# ======================================================================================================================================

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.8.0)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# ======================================================================================================================================
# include directories
# ======================================================================================================================================
include_directories(${CMAKE_CURRENT_LIST_DIR}/../src)

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# MessageInfo unit tests
file(GLOB_RECURSE MESSAGE_INFO_UNIT_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/messageInfoTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/messageInfoTest.h")

# AsyncFileAccess unit tests
file(GLOB_RECURSE ASYNC_FILE_ACCESS_UNIT_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/asyncFileAccessTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/asyncFileAccessTest.h")

# ======================================================================================================================================
# Create dependencies libraries
# ======================================================================================================================================

# Create the memory leak detector library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/memoryLeakDetector ${CMAKE_CURRENT_LIST_DIR}/../../../../../build/unitTests/memoryLeakDetector)

# ======================================================================================================================================
# create the unit tests executables
# ======================================================================================================================================

add_executable(messageInfoUnitTests ${MESSAGE_INFO_UNIT_TESTS_SRC})

add_executable(asyncFileAccessUnitTests ${ASYNC_FILE_ACCESS_UNIT_TESTS_SRC})

# ======================================================================================================================================
# link the each executable with all relevant libraries
# ======================================================================================================================================

target_link_libraries(messageInfoUnitTests gtest gtest_main memoryLeakDetectorLib sqsFsLib)

target_link_libraries(asyncFileAccessUnitTests gtest gtest_main memoryLeakDetectorLib sqsFsLib)

# ======================================================================================================================================
# GTest realted settings
# ======================================================================================================================================

add_test(messageInfoUnitTests messageInfoUnitTests)

add_test(asyncFileAccessUnitTests asyncFileAccessUnitTests)


