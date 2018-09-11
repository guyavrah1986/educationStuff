# ======================================================================================================================================
# general project settings
# ======================================================================================================================================
cmake_minimum_required(VERSION 3.5)

project(internalLibraries)

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# ======================================================================================================================================
# include directories
# ======================================================================================================================================

include_directories(${CMAKE_CURRENT_LIST_DIR}/include
		    ${CMAKE_CURRENT_LIST_DIR}/../utils/http-server-mongoose)

# ======================================================================================================================================
# group all source files of the library
# ======================================================================================================================================
file(GLOB_RECURSE TS_LIBS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/src/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") 

file(GLOB_RECURSE TS_LIBS_HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/include/*.h")

# mogoose related source files
file(GLOB_RECURSE TS_MONGOOSE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/../utils/http-server-mongoose/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/../utils/http-server-mongoose/*.h")

# ======================================================================================================================================
# create the library
# ======================================================================================================================================
add_library(tsLibs SHARED ${TS_LIBS_SRC} ${TS_MONGOOSE_SRC} ${TS_LIBS_HEADERS})

# ======================================================================================================================================
# link the library with all other needed libraries
# ======================================================================================================================================

