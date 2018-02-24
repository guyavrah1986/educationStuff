# README #

This repositroy holds sample code that emulates the Spirent IoT client SDK.

# Settings #

In order to build the project into eclipse IDE:
a) Run the buildSpirentCodeProject.sh script as follows:
$ buildSpirentCodeProject.sh ..

b) Add C++11 index settings:
Go to: Project --> Properties --> C/C++ General --> Preprocessor Include Paths, Macros etc. --> Providers (tab) --> CDT GCC Built-in Compiler Settings.
Add the c++11 flag at the end of the "Command to get compiler spec" tab (see below):
${COMMAND} ${FLAGS} -E -P -v -dD "${INPUTS}" -std=c++11

c) Open eclipse IDE and import the project as a CMake project.

d) Add the build folder to the build location:
${workspace_loc:/spirentCode}/ --> ${workspace_loc:/spirentCode}/build

e) Build the project

f) Project --> C++ Indexer --> Rebuild. 
