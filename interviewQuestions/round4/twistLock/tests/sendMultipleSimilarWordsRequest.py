import sys
import random 

import time
from termcolor import colored

import utils

# ===========================================================================================================================================
# ===========================================================================================================================================

def invokeGetStatsRequestMethod(results, index):
	results[index] = utils.SendGetRequest("stats")

def invokeGetSimilarWordsRequestMethod(results, index, reqType):
	request = "similar?word=" + dbListOfWords[reqType]
	utils.SendGetRequest(request)

# ===========================================================================================================================================
# ===========================================================================================================================================

# global arrays:
numberOfThreadsForEachQueriedWord = 5
numOfReqToSend = 10

listOfWordsToQuery = ["bgu", "appel", "aah", "benzdioxdiazine", "doesNotExistsWord"]
numOfTypesOfRequests = len(listOfWordsToQuery) # one for each different word

# exists - no matches
reqType0Word = "bgu"

# exists - 2 matches
reqType1Word = "appel"

# exists - no matches
reqType2Word = "aah"

# exists - 1 matches
reqType3Word = "benzdioxdiazine"

# does not exist - no matches
reqType4Word = "doesNotExistsWord"

exitStatusCode = 0
totalNumberOfWordsInDb = 351075
totalRequests = 0
dbFileName = "words_clean.txt"

# first - start the server
serverProc = utils.StartServer("serverExe", dbFileName)

# wait for a moment while the server is booting
time.sleep(5)

for i in range(1, numOfReqToSend):
	reqType = random.randint(0, len(listOfWordsToQuery) - 1)  # will resolve in [0-4]
	request = "similar?word=" + listOfWordsToQuery[reqType]
	utils.SendGetRequest(request)

print ""
print ""
print colored("=====================================", "blue")
print colored("Done sending all the" + str(numOfReqToSend), "blue")
print colored("=====================================", "blue")
print ""
print ""

utils.ExitScript(exitStatusCode, serverProc)

