# Collect sources into the variable LIB1_SOURCES without
# having to explicitly list each header and source file.
#
# CMake documentation states "We do not recommend using GLOB to collect a
# list of source files from your source tree. If no CMakeLists.txt file
# changes when a source is added or removed then the generated build system
# cannot know when to ask CMake to regenerate".
file (GLOB LIB1_SOURCES
      "*.h"
      "*.cpp")
 
# Create named folders for the sources within the .vcproj
# source_group("" FILES ${LIB1_SOURCES}) - Empty name lists them directly under the .vcproj
source_group("lib1" FILES ${LIB1_SOURCES})
 
# Properties->C/C++->General->Additional Include Directories
include_directories (.)
 
# Set Properties->General->Configuration Type to Static Library(.lib)
# Creates lib1.lib (and NOT lib1.dll as with SHARED libraries) composed from the listed sources collected in the variable LIB1_SOURCES
# Also adds sources to the Solution Explorer
add_library(lib1 STATIC ${LIB1_SOURCES})
 
# Creates folder "libraries" and adds target project (lib1.vcproj)
set_property(TARGET lib1 PROPERTY FOLDER "libs")
 
# Properties->General->Output Directory
set_target_properties(lib1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Adds logic to INSTALL.vcproj to copy lib1.dll to the destination directory
install(TARGETS lib1
		ARCHIVE DESTINATION lib1
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install)