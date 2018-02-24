# =====================================================================================================================================
# general project settings
# =====================================================================================================================================

cmake_minimum_required(VERSION 3.5)

project("spirentCodeSample")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# set the output directory for tje executables, static and shared libraries are placed once finished to the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

# enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ======================================================================================================================================
# include directories
# ======================================================================================================================================
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# executable files
file(GLOB_RECURSE SPIRENT_CODE_EXE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/samples/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/samples/*.h")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================


# disable specific warnings (intentionally stated AFTER the unitTest --> GTests framework ahs TONS of warnings which slows the compilation process)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option -Wno-pmf-conversions")

# the "main" SDK library (spirentLib)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/build/src)

# unitTests
set(CMAKE_CXX_FLAGS "") # disable all the warnings that were set earlier -- otherwise GTest will produce TONS of errors
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/unitTests ${CMAKE_CURRENT_LIST_DIR}/build/unitTests)

# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
   
add_executable(spirentCodeExe ${SPIRENT_CODE_EXE_SRC})

# ======================================================================================================================================
# link the executable with all relevant libraries
# ======================================================================================================================================
                 
target_link_libraries(spirentCodeExe spirentLib)

