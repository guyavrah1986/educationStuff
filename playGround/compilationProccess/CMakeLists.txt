# ======================================================================================================================================
# general project settings
# ======================================================================================================================================

cmake_minimum_required(VERSION 3.5)

project("compilationProccess")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR})
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR})

# ======================================================================================================================================
# include directories
# ======================================================================================================================================

include_directories(${CMAKE_CURRENT_LIST_DIR}/lib1
					${CMAKE_CURRENT_LIST_DIR}/lib2)

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

file(GLOB COMPILATION_PROCCESS_EXE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/exeFolder/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/exeFolder/*.h")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================

# lib1 
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/exeFolder/lib1 /${CMAKE_CURRENT_LIST_DIR}/build)

# lib2
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/exeFolder/lib2 /${CMAKE_CURRENT_LIST_DIR}/build)


# ======================================================================================================================================
# create the main executable
# ======================================================================================================================================

add_executable(cppCompilationProcessExe ${COMPILATION_PROCCESS_EXE_SRC})

# ======================================================================================================================================
# link the main executable with all relevant libraries
# ======================================================================================================================================

target_link_libraries(cppCompilationProcessExe lib2)

                    
