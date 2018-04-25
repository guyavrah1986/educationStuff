cmake_minimum_required (VERSION 3.10)

# Maps to Visual Studio solution file (vector.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project(vector)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Properties->C/C++->General->Additional Include Directories
include_directories(.)
 
# Set Properties->General->Configuration Type to Application(.exe)
# Creates item1Exe.exe with the listed sources (vector.cpp)
# Adds sources to the Solution Explorer
add_executable(vectorExe MyObjNoDefualtCtor.cpp 
						 MyObjNoDefualtCtor.h 
						 MyObj.cpp
						 MyObj.h
						 MyObjsOperators.h
						 vector1Exaplained.h
						 vector1Exaplained.cpp
						 vector.cpp)
 
# Properties->Linker->Input->Additional Dependencies
# target_link_libraries(vectorExe)
 
# Creates a folder "executables" and adds target 
# project (vectorExe.vcproj) under it
set_property(TARGET vectorExe PROPERTY FOLDER "executables")
 
# Properties->General->Output Directory
set_target_properties(vectorExe PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Solution Properties->Startup Project->Single Startup project 
# Set this executable to be the startup project of the vector solution (availble from cmake 3.6)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vectorExe)
 
# Adds logic to INSTALL.vcproj to copy vector.exe to destination directory
install (TARGETS vectorExe
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)