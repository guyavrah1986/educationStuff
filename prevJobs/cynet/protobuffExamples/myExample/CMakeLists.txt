# Minimum CMake required
cmake_minimum_required(VERSION 3.10)

# Project
project(myProtobufBasicExample)

message(STATUS "proccessing CMakeLists.txt file within:${CMAKE_CURRENT_LIST_DIR}")
set(protobuf_DIR "${CMAKE_CURRENT_LIST_DIR}/../protobuf-cpp-3.5.1/install/cmake") 

# Find required protobuf package
find_package(protobuf CONFIG REQUIRED)

if(protobuf_VERBOSE)
  message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# http://www.cmake.org/Wiki/CMake_FAQ#How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
if(MSVC AND protobuf_MSVC_STATIC_RUNTIME)
  foreach(flag_var
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
  endforeach()
endif()

# Add the source files into a list
set(BASIC_PROTOBUF_EXAMPLE_SRC basicProtobufExampleMain.cpp)

# Add the .proto files into a list
set(BASIC_PROTOBUF_EXAMPLE_PROTOS basicProtobufProtoFile.proto)

#Code Generation
if(protobuf_MODULE_COMPATIBLE) #Legacy Support
	protobuf_generate_cpp(basicProtobufExample_PROTO_SRCS basicProtobufExample_PROTO_HDRS ${BASIC_PROTOBUF_EXAMPLE_PROTOS})
    list(APPEND basicProtobufExample_SRCS basicProtobufExample_PROTO_SRCS basicProtobufExample_PROTO_HDRS)
endif()

#Executable setup
set(executable_name basicProtobufExample_cpp)
add_executable(${executable_name} ${BASIC_PROTOBUF_EXAMPLE_SRC} ${BASIC_PROTOBUF_EXAMPLE_PROTOS})

if(protobuf_MODULE_COMPATIBLE) #Legacy mode
	target_include_directories(${executable_name} PUBLIC ${Protobuf_INCLUDE_DIR})
    target_link_libraries(${executable_name} ${Protobuf_LIBRARY})
else()
    target_link_libraries(${executable_name} protobuf::libprotobuf)
    protobuf_generate(TARGET ${executable_name})
endif()
