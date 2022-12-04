#!/bin/bash
# ============================================================================================
# 
# ============================================================================================


# get current directory
echo "Running script `basename $0`"
echo "---------------------------------"

# go "up" to the root folder, AKA ts-task
base_folder_name="ts-task"
#cd "${PWD/\/$base_folder\/*//$base_folder}"
base_folder=$(pwd)
echo "currently within:$base_folder"

executalbesFolder='/build/build'
executalbesFolderFullPath=$base_folder$executalbesFolder

# copy all the test files in the textFiles folder into the build/build folder
# so that the unit tests and component tests will run correctly
textFilesFolderName='/textFiles/'
textFilesFolderFullPath=$base_folder$textFilesFolderName
cp -a $textFilesFolderFullPath $executalbesFolderFullPath

# move the the directory where the executables are
cd build/build

# run all the unit tests executable one-by-one

#1) 
echo "Running dbManagerUnitTests" 
echo "--------------------------"
"./dbManagerUnitTests"
echo ""

#2)
echo "Running jsonUnitTests" 
echo "---------------------"
"./jsonUnitTests"
echo ""

#3)
echo "Running similarWordsResolverUnitTests" 
echo "-------------------------------------"
"./similarWordsResolverUnitTests"
echo ""

#4)
echo "Running statsResolverUnitTests" 
echo "------------------------------"
"./statsResolverUnitTests"
echo ""

#5)
echo "Running requestNavigatorUnitTests" 
echo "---------------------------------"
"./requestNavigatorUnitTests"
echo ""

#6)
echo "Running hashDbManagerUnitTests" 
echo "------------------------------"
"./hashDbManagerUnitTests"
echo ""


