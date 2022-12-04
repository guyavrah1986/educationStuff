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
		str=$2$" -- PASSED"
		chosenColor=`tput setaf 2` # green
	else
		str=$2$" -- FAILED"
		chosenColor=`tput setaf 1` # red

	fi
	reset=`tput sgr0` # no color
	echo "${chosenColor}==============================================================================="
	echo "${chosenColor}==============================================================================="
  	echo ${chosenColor}$str
	echo "${chosenColor}==============================================================================="
	echo "${chosenColor}===============================================================================${reset}"
	echo ""
	echo ""
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

# 1) singleGetStatsRequestTest
# ----------------------------
echo "=================================="
echo "running singleGetStatsRequestTest"
echo "=================================="
testToRunFullPath=''
composeTestToRunFullPath "singleGetStatsRequestTest.py" testToRunFullPath
python $testToRunFullPath
retVal=$?
testRetValCheck $retVal "singleGetStatsRequestTest"

# 2) singleGetSimilarWordsRequestTest
# -----------------------------------
echo "========================================"
echo "running singleGetSimilarWordsRequestTest"
echo "========================================"
testToRunFullPath=''
composeTestToRunFullPath "singleGetSimilarWordsRequestTest.py" testToRunFullPath
python $testToRunFullPath
testRetValCheck $retVal "singleGetSimilarWordsRequestTest"


# 3) updateAvgProcTimeNsTest
# --------------------------
echo "==============================="
echo "running updateAvgProcTimeNsTest"
echo "==============================="
testToRunFullPath=''
composeTestToRunFullPath "updateAvgProcTimeNsTest.py" testToRunFullPath
python $testToRunFullPath
testRetValCheck $retVal "updateAvgProcTimeNsTest"


# 4) singleGetSimilarWordForWordThatDoesNotExsitsTest
# ---------------------------------------------------
echo "========================================================"
echo "running singleGetSimilarWordForWordThatDoesNotExsitsTest"
echo "========================================================"
testToRunFullPath=''
composeTestToRunFullPath "singleGetSimilarWordForWordThatDoesNotExsitsTest.py" testToRunFullPath
python $testToRunFullPath
testRetValCheck $retVal "singleGetSimilarWordForWordThatDoesNotExsitsTest"

# 5) sendSIGINTSignalToServerTest
# -------------------------------
echo "===================================="
echo "running sendSIGINTSignalToServerTest"
echo "===================================="
testToRunFullPath=''
composeTestToRunFullPath "sendSIGINTSignalToServerTest.py" testToRunFullPath
python $testToRunFullPath
testRetValCheck $retVal "sendSIGINTSignalToServerTest"

# 6) singleGetSimilarWordForWordThatExsitsWithNoSimilarWordsTest
# --------------------------------------------------------------
echo "==================================================================="
echo "running singleGetSimilarWordForWordThatExsitsWithNoSimilarWordsTest"
echo "==================================================================="
testToRunFullPath=''
composeTestToRunFullPath "singleGetSimilarWordForWordThatExsitsWithNoSimilarWordsTest.py" testToRunFullPath
python $testToRunFullPath
testRetValCheck $retVal "singleGetSimilarWordForWordThatExsitsWithNoSimilarWordsTest"


# 7) singleGetSimilarWordsRequestURITooLongTest
# ---------------------------------------------
echo "======================================================"
echo "running singleGetSimilarWordsRequestURITooLongTest.py"
echo "======================================================"
testToRunFullPath=''
composeTestToRunFullPath "singleGetSimilarWordsRequestURITooLongTest.py" testToRunFullPath
python $testToRunFullPath
testRetValCheck $retVal


# 8) sendInvalidRequestsTypes
# ---------------------------
echo "===================================="
echo "running sendInvalidRequestsTypes.py"
echo "==================================="
testToRunFullPath=''
composeTestToRunFullPath "sendInvalidRequestsTypes.py" testToRunFullPath
python $testToRunFullPath
testRetValCheck $retVal "sendInvalidRequestsTypes"


# 9) singleGetSimilarWordForEmptyWordTest
# ---------------------------------------
echo "============================================="
echo "running singleGetSimilarWordForEmptyWordTest"
echo "============================================="
testToRunFullPath=''
composeTestToRunFullPath "singleGetSimilarWordForEmptyWordTest.py" testToRunFullPath
python $testToRunFullPath
testRetValCheck $retVal "singleGetSimilarWordForEmptyWordTest"

echo "Performing cleanup"
cleanup "serverExe"


echo ""
echo ""
echo "**********************"
echo "**********************"
echo "Done running all tests"
echo "**********************"
echo "**********************"
