# =====================================================================================================================================
# general project settings
# ======================================================================================================================================
cmake_minimum_required(VERSION 3.9)

project("sampleUsageStdThreasRaiiWrapper")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# set the output directory for the executables, static and shared libraries are placed once finished to the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

# enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================================================================================================
# include directories
# ======================================================================================================================================
include_directories(${CMAKE_CURRENT_LIST_DIR}/wrapperLib)

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================
file(GLOB_RECURSE MAIN_EXE_SRC "${CMAKE_CURRENT_LIST_DIR}/main.cpp") 

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================
# utilities
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/wrapperLib/ ${CMAKE_CURRENT_LIST_DIR}/build/wrapperLib)

# unitTests
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/unitTests ${CMAKE_CURRENT_LIST_DIR}/build/unitTests)


# ======================================================================================================================================
# create the main executable
# ======================================================================================================================================
add_executable(mainExe ${MAIN_EXE_SRC})
   
# ======================================================================================================================================
# link the main executable with all relevant libraries
# ======================================================================================================================================             
target_link_libraries(mainExe pthread glog) # stdThreadRaiiWrapperLib

