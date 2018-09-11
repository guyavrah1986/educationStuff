# ======================================================================================================================================
# general project settings
# ======================================================================================================================================
cmake_minimum_required(VERSION 3.5.1)

project(unitTests)

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


# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# JSON unit tests
file(GLOB_RECURSE TS_SRC_JSON_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/jsonTests/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/jsonTests/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/../utils/json/src/*.hpp") 

# DbManager unit tests
file(GLOB_RECURSE TS_SRC_DB_MANAGER_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/dbManagerTest/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/dbManagerTest/*.h")

# Word's permutations Resolver unit tests
file(GLOB_RECURSE TS_SIMILAR_WORDS_RESOLVER_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/similarWordsResolverTests/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/similarWordsResolverTests/*.h")

# stats resolver unit tests
file(GLOB_RECURSE TS_STATS_RESOLVER_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/statsResolverTests/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/statsResolverTests/*.h")

# request navigator unit tests
file(GLOB_RECURSE TS_REQUEST_NAVIGATOR_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/requestNavigatorTests/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/requestNavigatorTests/*.h")

# HasDbManager unit tests
file(GLOB_RECURSE TS_HASH_DB_MANAGER_TESTS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/hashDbManagerTests/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/hashDbManagerTests/*.h")
# ======================================================================================================================================
# Create dependencies libraries
# ======================================================================================================================================

# Create the memory leak detector library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/memoryLeakDetector ${CMAKE_CURRENT_LIST_DIR}/../build/unitTests/memoryLeakDetector)

# ======================================================================================================================================
# create the unit tests executables
# ======================================================================================================================================

add_executable(jsonUnitTests ${TS_SRC_JSON_TESTS_SRC})

add_executable(similarWordsResolverUnitTests ${TS_SIMILAR_WORDS_RESOLVER_TESTS_SRC})

add_executable(statsResolverUnitTests ${TS_STATS_RESOLVER_TESTS_SRC})

add_executable(requestNavigatorUnitTests ${TS_REQUEST_NAVIGATOR_TESTS_SRC})

add_executable(hashDbManagerUnitTests ${TS_HASH_DB_MANAGER_TESTS_SRC})

# ======================================================================================================================================
# link the each executable with all relevant libraries
# ======================================================================================================================================

target_link_libraries(jsonUnitTests gtest gtest_main memoryLeakDetectorLib common)

target_link_libraries(similarWordsResolverUnitTests gtest gtest_main memoryLeakDetectorLib tsLibs common)

target_link_libraries(statsResolverUnitTests gtest gtest_main memoryLeakDetectorLib tsLibs common)

target_link_libraries(requestNavigatorUnitTests gtest gtest_main memoryLeakDetectorLib tsLibs common)

target_link_libraries(hashDbManagerUnitTests gtest gtest_main memoryLeakDetectorLib tsLibs common)

# ======================================================================================================================================
# GTest realted settings
# ======================================================================================================================================

add_test(jsonUnitTests jsonUnitTests)

add_test(similarWordsResolverUnitTests similarWordsResolverUnitTests)

add_test(statsResolverUnitTests statsResolverUnitTests)

add_test(requestNavigatorUnitTests requestNavigatorUnitTests)

add_test(hashDbManagerUnitTests hashDbManagerUnitTests)

