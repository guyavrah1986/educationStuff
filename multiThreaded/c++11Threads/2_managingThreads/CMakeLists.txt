# ======================================================================================================================================
# general project settings
# ======================================================================================================================================
cmake_minimum_required(VERSION 3.10)

project("managingThreads")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR})

# enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# get the OS specific threading library (needed for std::thread)
find_package(Threads REQUIRED)

# ======================================================================================================================================
# include directories
# ======================================================================================================================================
#include_directories(${CMAKE_CURRENT_LIST_DIR})

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

file(GLOB MANAGING_THREADS_EXE_SRC "${CMAKE_CURRENT_LIST_DIR}/managingThreadsMain.cpp"
								   "${CMAKE_CURRENT_LIST_DIR}/myMovedObj.h")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/exeFolder/lib1 /${CMAKE_CURRENT_LIST_DIR}/build)


# ======================================================================================================================================
# create the main executable
# ======================================================================================================================================
add_executable(managingThreadsExe ${MANAGING_THREADS_EXE_SRC})

# ======================================================================================================================================
# link the main executable with all relevant libraries
# ======================================================================================================================================
target_link_libraries(managingThreadsExe Threads::Threads)

                    
