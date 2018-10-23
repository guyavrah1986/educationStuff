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
include_directories(${CMAKE_CURRENT_LIST_DIR}/../src
		    ${CMAKE_CURRENT_LIST_DIR}/mallocAndFreeWrappersForUnitTests)

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# CRsrcBase unit tests
file(GLOB_RECURSE FLOAT_RSRC_BASE_UNIT_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/floatRsrcUnitTests/floatRsrcBaseTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/floatRsrcUnitTests/floatRsrcBaseTests.h"
    "${CMAKE_CURRENT_LIST_DIR}/mallocAndFreeWrappersForUnitTests/mallocAndFreeWrappers.h"
    "${CMAKE_CURRENT_LIST_DIR}/mallocAndFreeWrappersForUnitTests/mallocAndFreeWrappers.c")

# CAdapterMgr unit tests
file(GLOB_RECURSE ADAPTER_MGR_UNIT_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/adapterMgrUnitTests/adapterMgrTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/adapterMgrUnitTests/adapterMgrTests.h"
    "${CMAKE_CURRENT_LIST_DIR}/mallocAndFreeWrappersForUnitTests/mallocAndFreeWrappers.h"
    "${CMAKE_CURRENT_LIST_DIR}/mallocAndFreeWrappersForUnitTests/mallocAndFreeWrappers.c")

# CRsrcMgr unit tests
file(GLOB_RECURSE RSRC_MGR_UNIT_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/rsrcMgrUnitTests/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/rsrcMgrUnitTests/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/mallocAndFreeWrappersForUnitTests/mallocAndFreeWrappers.h"
    "${CMAKE_CURRENT_LIST_DIR}/mallocAndFreeWrappersForUnitTests/mallocAndFreeWrappers.c")

# ======================================================================================================================================
# Create dependencies libraries
# ======================================================================================================================================


# ======================================================================================================================================
# create the unit tests executables
# ======================================================================================================================================

add_executable(floatRsrcBaseTestsUnitTestsExe ${FLOAT_RSRC_BASE_UNIT_TESTS_SRC})

add_executable(rsrcMgrTestsUnitTestsExe ${RSRC_MGR_UNIT_TESTS_SRC})

add_executable(adapterMgrTestsUnitTestsExe ${ADAPTER_MGR_UNIT_TESTS_SRC})

# ======================================================================================================================================
# link the each executable with all relevant libraries
# ======================================================================================================================================

target_link_libraries(floatRsrcBaseTestsUnitTestsExe gtest gtest_main spirentLib)

target_link_libraries(rsrcMgrTestsUnitTestsExe gtest gtest_main spirentLib)

target_link_libraries(adapterMgrTestsUnitTestsExe gtest gtest_main spirentLib)

# ======================================================================================================================================
# GTest realted settings
# ======================================================================================================================================

add_test(floatRsrcBaseTestsUnitTestsExe floatRsrcBaseTestsUnitTestsExe)

add_test(adapterMgrTestsUnitTestsExe adapterMgrTestsUnitTestsExe)

add_test(rsrcMgrTestsUnitTestsExe rsrcMgrTestsUnitTestsExe)


