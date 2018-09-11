# =====================================================================================================================================
# general project settings
# ======================================================================================================================================
cmake_minimum_required(VERSION 3.5)

project("ts-task")

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

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/include)		# all internal libraries header files are here
include_directories(${CMAKE_CURRENT_LIST_DIR}/utils/http-server-mongoose)
		    
# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# mogoose related source files
file(GLOB_RECURSE TS_MONGOOSE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/utils/http-server-mongoose/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/utils/http-server-mongoose/*.h")

# RESTfull sample sources
file(GLOB_RECURSE TS_SERVER_EXE_SRC
    "${CMAKE_CURRENT_LIST_DIR}/samples/server/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/samples/server/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/samples/server/*.h")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================

# common library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common ${CMAKE_CURRENT_LIST_DIR}/build/common)

# internal libraries (accumulated to a single library)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/build/src)

# unitTests
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/unitTests ${CMAKE_CURRENT_LIST_DIR}/build/unitTests)

# C++ component tests
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests/cppBasedTests/httpClientBoost ${CMAKE_CURRENT_LIST_DIR}/build/tests)

# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
   
add_executable(serverExe ${TS_SERVER_EXE_SRC} ${TS_MONGOOSE_SRC} ${TS_DB_MANAGER_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================
                 
target_link_libraries(serverExe tsLibs common pthread)


