#!/bin/bash

function checkLastCommandStatusAnddisplayErrorMsgIfNeeded {
	if [ ! $? -eq 0 ]
	then
		echo "error occured when trying to $1, aborting"
		exit 1
	fi	
}

echo "==============================="
echo "$0 - start"
echo "==============================="

currDir=`(pwd)`
echo "current directory is:$currDir"

# if build folder exists - delete it along with all 
# its content
buildFolderName=build
if [ -d "$buildFolderName" ]
then
	echo "$buildFolderName exists, removing it"
	rm -rf $buildFolderName
fi 

# create the (new) build folder
mkdir build
checkLastCommandStatusAnddisplayErrorMsgIfNeeded "create $buildFolderName"

# navigate to the build folder
cd $buildFolderName
cmakeCommandToInvoke="cmake .."

# invoke the desired cmake command
$cmakeCommandToInvoke
checkLastCommandStatusAnddisplayErrorMsgIfNeeded "to run command:$cmakeCommandToInvoke"

echo "==============================="
echo "$0 - end"
echo "==============================="
