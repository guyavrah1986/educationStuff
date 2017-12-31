# =====================================================================================================================================
# general project settings
# =====================================================================================================================================

cmake_minimum_required(VERSION 3.5)

project("cppStuff")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================================================================================================
# disable specific warnings
# ======================================================================================================================================

set(CPP_STUFF_WARNINGS "-Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS ${CPP_STUFF_WARNINGS}) #"${CMAKE_CXX_FLAGS} -Wno-pmf-conversions")
endif()


# ======================================================================================================================================
# include directories
# ======================================================================================================================================

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# virtual table explantation sources
file(GLOB_RECURSE VTABLE_EXPLANIED_SRC
    "${CMAKE_CURRENT_LIST_DIR}/virtualTableExplained.cpp")

# std::vector explantation sources
file(GLOB_RECURSE VECTOR_EXPLANIED_SRC
    "${CMAKE_CURRENT_LIST_DIR}/vectorExplained.cpp")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================

# common library
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common ${CMAKE_CURRENT_LIST_DIR}/build/common)

# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
   
add_executable(vtableExplaniedExe ${VTABLE_EXPLANIED_SRC})

add_executable(vectorExplainedExe ${VECTOR_EXPLANIED_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================
                 

