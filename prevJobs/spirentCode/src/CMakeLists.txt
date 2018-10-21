# ======================================================================================================================================
# general project settings
# ======================================================================================================================================
cmake_minimum_required(VERSION 3.5)

project(spirentLib)

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# ======================================================================================================================================
# include directories
# ======================================================================================================================================
include_directories("${CMAKE_CURRENT_LIST_DIR}"
		    "${CMAKE_CURRENT_LIST_DIR}/adapter"
		    "${CMAKE_CURRENT_LIST_DIR}/core"
		    "${CMAKE_CURRENT_LIST_DIR}/rsrc"
	 	    "${CMAKE_CURRENT_LIST_DIR}/statsModule")

# ======================================================================================================================================
# group all source files of the library
# ======================================================================================================================================

file(GLOB_RECURSE SPIRENT_SRC_LIBS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/adapter/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/adapter/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/core/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/core/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/rsrc/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/rsrc/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/statsModule/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/statsModule/*.cpp") 


# ======================================================================================================================================
# create the library
# ======================================================================================================================================
add_library(spirentLib SHARED ${SPIRENT_SRC_LIBS_SRC})

# ======================================================================================================================================
# link the library with all other needed libraries
# ======================================================================================================================================

