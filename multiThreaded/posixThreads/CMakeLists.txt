# =====================================================================================================================================
# general project settings
# =====================================================================================================================================
cmake_minimum_required(VERSION 3.10)

project("posixThreads")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# enable c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ======================================================================================================================================
# disable specific warnings
# ======================================================================================================================================
# used to enable (almost) all warnings
set(POSIX_THREADS_WARNINGS "-Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization 
-Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow
-Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS ${POSIX_THREADS_WARNINGS})
endif()

# ======================================================================================================================================
# include directories
# ======================================================================================================================================

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================
# virtual table explantation sources
file(GLOB_RECURSE POSIX_THREADS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/posixThreadsCondVarAndMutexSimpleUsage.c.c")

	
# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================

# common library
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common ${CMAKE_CURRENT_LIST_DIR}/build/common)

# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
add_executable(posixThreadsCondVarAndMutexSimpleUsageExe ${POSIX_THREADS_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================
if (UNIX AND NOT APPLE)
	target_link_libraries(posixThreadsCondVarAndMutexSimpleUsageExe pthread)                 
endif()
