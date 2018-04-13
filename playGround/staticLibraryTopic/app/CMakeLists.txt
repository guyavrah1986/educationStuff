# Properties->C/C++->General->Additional Include Directories
include_directories ("${PROJECT_SOURCE_DIR}/lib1")
  
# Set Properties->General->Configuration Type to Application(.exe)
# Creates app with the listed sources (main.cpp)
# Adds sources to the Solution Explorer
add_executable(app main.cpp)
 
# Properties->Linker->Input->Additional Dependencies (Note: for the respective project, in this case app)
target_link_libraries(app lib1)
 
# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
set_property(TARGET app PROPERTY FOLDER "executables")
 
# Properties->General->Output Directory
set_target_properties(app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
					  
# Solution Properties->Startup Project->Single Startup project 
# Set this executable to be the startup project of the staticLibraryExample solution (availble from cmake 3.6)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT app)
 
# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS app
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)