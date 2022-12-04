#! /bin/bash

# =============================================================================================================================================================
# =============================================================================================================================================================
# =============================================================================================================================================================
# functions section:
# -----------------
function testRetValCheck {
	str=''
	chosenColor=''
	if [ "$1" -eq 0 ]
	then
		str=$2$"-- PASSED"
		chosenColor=`tput setaf 2` # green
	else
		str=$2$"-- FAILED"
		chosenColor=`tput setaf 1` # red

	fi
	reset=`tput sgr0` # no color
	echo "${chosenColor}==============================================================================="
	echo "${chosenColor}==============================================================================="
  	echo ${chosenColor}$str
	echo "${chosenColor}==============================================================================="
	echo "${chosenColor}===============================================================================${reset}"
}

function composeTestToRunFullPath {
	local curr_folder=$(pwd)
	local testToRunPrefix="/tests/"
	testToRun=$curr_folder$testToRunPrefix$1
    	eval "$2='$testToRun'"
}

function cleanup {
	pid=$(pgrep "serverExe") 
	kill $pid
	echo "cleanup - killed PID:$pid"	
}


# =============================================================================================================================================================
# =============================================================================================================================================================
# =============================================================================================================================================================

# Run the following tests:
# -----------------------

# 1) sendStatsAndSimilarWordsRequestWithSeveralThreads
# ----------------------------------------------------
echo "=========================================================="
echo "running sendStatsAndSimilarWordsRequestWithSeveralThreads"
echo "=========================================================="
testToRunFullPath=''
composeTestToRunFullPath "sendStatsAndSimilarWordsRequestWithSeveralThreads.py" testToRunFullPath
python $testToRunFullPath
retVal=$?
testRetValCheck $retVal "sendStatsAndSimilarWordsRequestWithSeveralThreads"

echo "Performing cleanup"
cleanup

echo ""
echo ""
echo "**********************"
echo "**********************"
echo "Done running all tests"
echo "**********************"
echo "**********************"
