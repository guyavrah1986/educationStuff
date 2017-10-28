# ======================
# Name the project
# ======================
cmake_minimum_required(VERSION 3.5)
project(common_utilities)

# ===========================================================
# Add all the source and header files that are relevant for 
# the library
# ============================================================
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC
    "${CMAKE_CURRENT_LIST_DIR}/src/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") 

file(GLOB HEADERS
    "*.h")

add_library(commonUtilities SHARED ${SRC} ${HEADERS})

                    
