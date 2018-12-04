#!/bin/bash
# ==========================================================================================================================================
# This script is meant to be run by the Jenkins server upon each "change" it notified in the GitHub repository that holds this project.
# ==========================================================================================================================================

# define the path to the CMakeLists.txt we wish to invoke (currently "hard-coded"
# might be better to sent it as an argument for this script)
cmake_file_full_path=".."

# check if the "output" directory for the Jenkins server exists
output_build_dir_name="build"
if [ -d "$output_build_dir_name" ]; then
	echo "Deleting current Jenkins output build folder"
	sudo rm -r -f $output_build_dir_name
fi

# create a new empty "Jenkins output" build folder
mkdir $output_build_dir_name
echo "Created an empty output folder for the Jenkins build"
cd $output_build_dir_name

# invoke the cmake command to build the unit tests executable + all the relevant GTests  
echo "Invoking cmake on the desired CMakeLists file"
cmake -G "Unix Makefiles" -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 -DCMAKE_BUILD_TYPE=Release $cmake_file_full_path

# clean after the cmake command in the "main" (root) folder
#cd "${PWD/\/$base_folder\/*//$base_folder}"
cd ..
curr_folder=$(pwd)
echo "Cleaning after the cmake command leftovers within folder:$curr_folder"
sudo rm -rf .cproject
sudo rm -rf .project
