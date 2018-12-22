# =====================================================================================================================================
# general project settings
# =====================================================================================================================================
cmake_minimum_required(VERSION 3.10)

project("generalQuestions")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================================================================================================
# disable specific warnings
# ======================================================================================================================================
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option -Wno-pmf-conversions")

# ======================================================================================================================================
# include directories
# ======================================================================================================================================
include_directories("${CMAKE_CURRENT_LIST_DIR}/../common")

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================
# linked list source file(s)
set(LINKED_LIST_QUESTIONS_SRC "${CMAKE_CURRENT_LIST_DIR}/linkedList/linkedListQuestionsMain.cpp")

# stack source file(s)
set(STACK_QUESTIONS_SRC "${CMAKE_CURRENT_LIST_DIR}/stack/stackMain.cpp")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================
# common library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../common ${CMAKE_CURRENT_LIST_DIR}/build/common)

# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
add_executable(linkedListQuestionsExe ${LINKED_LIST_QUESTIONS_SRC})

add_executable(stackQuestionsExe ${STACK_QUESTIONS_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================             
target_link_libraries(linkedListQuestionsExe interviewQuestionsCommonLib)

target_link_libraries(stackQuestionsExe interviewQuestionsCommonLib)

