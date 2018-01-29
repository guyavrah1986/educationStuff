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
	set(CMAKE_CXX_FLAGS ${CPP_STUFF_WARNINGS}) # use this setting in order to disable a certain warning: -Wno-pmf-conversions
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

# this pointer location (address) sources
file(GLOB_RECURSE THIS_POINTER_LOCATION_SRC
    "${CMAKE_CURRENT_LIST_DIR}/thisPointerLocationExample.cpp")

# name hiding sources
file(GLOB_RECURSE NAME_HIDING_SRC
    "${CMAKE_CURRENT_LIST_DIR}/nameHidingExample.cpp")

# copy ctor Vs assignment operator sources
file(GLOB_RECURSE COPY_CTOR_AND_ASSGINMENT_OPERATOR_SRC
    "${CMAKE_CURRENT_LIST_DIR}/copyCtorAndAssginmentOperatorExample.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/copyCtorAndAssginmentOperatorExample.h")

# struct pointer example sources
file(GLOB_RECURSE STRUCT_POINTER_EXAMPLE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/structPointerExample.c")

# function templates example sources
file(GLOB_RECURSE FUNCTION_TEMPLATE_EXAMPLE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/functionTemplateExample.h"
    "${CMAKE_CURRENT_LIST_DIR}/functionTemplateExample.cpp")

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

add_executable(thisPointerLocationExe ${THIS_POINTER_LOCATION_SRC})

add_executable(nameHidingExe ${NAME_HIDING_SRC})

add_executable(copyCtorAndAssginmentOperatorExe ${COPY_CTOR_AND_ASSGINMENT_OPERATOR_SRC})

add_executable(structPointerExe ${STRUCT_POINTER_EXAMPLE_SRC})

add_executable(functionTemplateExe ${FUNCTION_TEMPLATE_EXAMPLE_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================
                 

