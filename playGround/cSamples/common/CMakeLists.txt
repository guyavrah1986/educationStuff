# ======================
# Name the project
# ======================
cmake_minimum_required(VERSION 3.5)

project(common_C_Samples_Utilities)

# ===========================================================
# Add all the source and header files that are relevant for 
# the library
# ============================================================
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE HS_C_SAMPLES_UTILTIES_SRC
    "${CMAKE_CURRENT_LIST_DIR}/src/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") 

file(GLOB HS_C_SAMPLES_UTILTIES_HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/include/*.h")

add_library(commonCSamplesUtilities SHARED ${HS_C_SAMPLES_UTILTIES_SRC} ${HS_C_SAMPLES_UTILTIES_HEADERS})

                    
