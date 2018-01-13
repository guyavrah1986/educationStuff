# =====================================================================================================================================
# general project settings
# =====================================================================================================================================

cmake_minimum_required(VERSION 3.5)

project("tasks")

message(STATUS "processing CMakeLists of project:${CMAKE_PROJECT_NAME} within folder:${CMAKE_CURRENT_LIST_DIR}")

# enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================================================================================================
# disable specific warnings
# ======================================================================================================================================

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pmf-conversions")

# ======================================================================================================================================
# include directories
# ======================================================================================================================================

# ======================================================================================================================================
# group all source files of the executable
# ======================================================================================================================================

# files relevant interview preperation for a specific company
file(GLOB_RECURSE BLOOM_SRC
    "${CMAKE_CURRENT_LIST_DIR}/bloom/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/bloom/*.h")

file(GLOB_RECURSE CYBER_REASON_SRC
    "${CMAKE_CURRENT_LIST_DIR}/cyberreason/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/cyberreason/*.h")

# files relevant interview questions (in general)
file(GLOB_RECURSE JOB_HUNT_QUESTIONS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/jobHuntQuestions/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/jobHuntQuestions/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/jobHuntQuestions/*.h")

file(GLOB_RECURSE CRACKING_THE_CODING_INTERVIEW_QUESTIONS_SRC
    "${CMAKE_CURRENT_LIST_DIR}/crackingTheCodingInterviewQuestions/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/crackingTheCodingInterviewQuestions/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/crackingTheCodingInterviewQuestions/*.h")

# ======================================================================================================================================
# add relevant sub directories -- invoke their CMakeLists.txt files
# ======================================================================================================================================

# common library
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common ${CMAKE_CURRENT_LIST_DIR}/build/common)

# ======================================================================================================================================
# create the main executable (and samples as well)
# ======================================================================================================================================
   
add_executable(bloomPreparationExe ${BLOOM_SRC})

add_executable(jobHuntQuestionsExe ${JOB_HUNT_QUESTIONS_SRC})

add_executable(cyberreasonExe ${CYBER_REASON_SRC})

add_executable(crackingTheCodingInterviewQuestionsExe ${CRACKING_THE_CODING_INTERVIEW_QUESTIONS_SRC})

# ======================================================================================================================================
# link the executable(s) with all relevant libraries
# ======================================================================================================================================
                 
target_link_libraries(crackingTheCodingInterviewQuestionsExe pthread)

