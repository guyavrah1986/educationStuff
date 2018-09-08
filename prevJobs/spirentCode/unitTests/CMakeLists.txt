# ======================================================================================================================================
# general project settings
# ======================================================================================================================================
cmake_minimum_required(VERSION 3.5.1)

project(unitTestsSpirentCode)

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

# CRsrcBase unit tests
file(GLOB_RECURSE FLOAT_RSRC_BASE_UNIT_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/floatRsrcBaseTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/floatRsrcBaseTests.h")

# CRsrcMgr unit tests
file(GLOB_RECURSE RSRC_MGR_UNIT_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/rsrcMgrTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/rsrcMgrTests.h")

# ======================================================================================================================================
# Create dependencies libraries
# ======================================================================================================================================

# Create the memory leak detector library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/memoryLeakDetector ${CMAKE_CURRENT_LIST_DIR}/../../../../../build/unitTests/memoryLeakDetector)

# ======================================================================================================================================
# create the unit tests executables
# ======================================================================================================================================

add_executable(floatRsrcBaseTestsUnitTestsExe ${FLOAT_RSRC_BASE_UNIT_TESTS_SRC})

add_executable(rsrcMgrTestsUnitTestsExe ${RSRC_MGR_UNIT_TESTS_SRC})

# ======================================================================================================================================
# link the each executable with all relevant libraries
# ======================================================================================================================================

target_link_libraries(floatRsrcBaseTestsUnitTestsExe gtest gtest_main memoryLeakDetectorLib spirentLib)

target_link_libraries(rsrcMgrTestsUnitTestsExe gtest gtest_main memoryLeakDetectorLib spirentLib)

# ======================================================================================================================================
# GTest realted settings
# ======================================================================================================================================

add_test(floatRsrcBaseTestsUnitTestsExe floatRsrcBaseTestsUnitTestsExe)

add_test(rsrcMgrTestsUnitTestsExe rsrcMgrTestsUnitTestsExe)

