cmake_minimum_required (VERSION 3.10)

# Maps to Visual Studio solution file (staticLibraryExample.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project(staticLibraryExample)

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates automatically the "CMakePredefinedTargets" folder and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj into this folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
 
# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
 
# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message("cxx Flags:" ${CMAKE_CXX_FLAGS})

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(app)
add_subdirectory(lib1)
