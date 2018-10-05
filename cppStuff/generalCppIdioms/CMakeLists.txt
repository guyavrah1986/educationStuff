# =====================================================================================================================================
# general project settings
# =====================================================================================================================================

cmake_minimum_required(VERSION 3.5)

project("generalCppIdioms")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# enable c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ======================================================================================================================================
# disable specific warnings
# ======================================================================================================================================

# used to enable (almost) all warnings
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

# Composition and Aggragation example sources
file(GLOB_RECURSE COMPOSITION_AND_AGGRAGATION_EXAMPLE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/objectCompositionAndAggragation.cpp")

# pointer to ampersand example sources
file(GLOB_RECURSE POINTER_TO_AMPERSAND_EXAMPLE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/pointerToAmpersand.cpp")
	
# g++ bug example sources
file(GLOB_RECURSE GPP_BUG_EXAMPLE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/g++Bug/*.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/g++Bug/*.h")
	
# move semantics sources
file(GLOB_RECURSE MOVE_SEMANTICS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/cpp11/moveSemantics.cpp")

# unique ptr (my implementation) sources
file(GLOB_RECURSE UNIQUE_PTR_SRC
    "${CMAKE_CURRENT_LIST_DIR}/cpp11/uniquePtrImpl.cpp")

# std::unique_ptr usages sources
file(GLOB_RECURSE STD_UNIQUE_PTR_SRC
    "${CMAKE_CURRENT_LIST_DIR}/cpp11/uniquePtrUsage.cpp")
	
	
# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================

# common library
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common ${CMAKE_CURRENT_LIST_DIR}/build/common)

# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
   
add_executable(vtableExplaniedExe ${VTABLE_EXPLANIED_SRC})

add_executable(thisPointerLocationExe ${THIS_POINTER_LOCATION_SRC})

add_executable(nameHidingExe ${NAME_HIDING_SRC})

add_executable(copyCtorAndAssginmentOperatorExe ${COPY_CTOR_AND_ASSGINMENT_OPERATOR_SRC})

add_executable(structPointerExe ${STRUCT_POINTER_EXAMPLE_SRC})

add_executable(functionTemplateExe ${FUNCTION_TEMPLATE_EXAMPLE_SRC})

add_executable(objectCompositionAndAggragationExe ${COMPOSITION_AND_AGGRAGATION_EXAMPLE_SRC})

add_executable(pointerToAmpersandExe ${POINTER_TO_AMPERSAND_EXAMPLE_SRC})

add_executable(moveSemanticsExe ${MOVE_SEMANTICS_SRC})

add_executable(uniqurPtrExe ${UNIQUE_PTR_SRC})

add_executable(stdUniqurPtrUsageExe ${STD_UNIQUE_PTR_SRC})

add_executable(baseClassWithPureVirtualFunctionsExe ${GPP_BUG_EXAMPLE_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================
if (UNIX AND NOT APPLE)
	target_link_libraries(moveSemanticsExe pthread)                 
endif()
