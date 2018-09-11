import sys

import utils

import thread
import random 
from threading import Thread
import time
from termcolor import colored

# ===========================================================================================================================================
# ===========================================================================================================================================

def invokeGetStatsRequestMethod(results, index):
	results[index] = utils.SendGetRequest("stats")

def invokeGetSimilarWordsRequestMethod(results, index, reqType):
	request = "similar?word=" + dbListOfWords[reqType]
	#numOfMillseccondsTowait = random.randint(0, 50)
	#time.sleep (numOfMillseccondsTowait / 1000.0);
	results[index] = utils.SendGetRequest(request)
# ===========================================================================================================================================
# ===========================================================================================================================================

# globaL arrays:
numberOfThreadsForEachQueriedWord = 5

resultsSimilarWordsType0 = [None] * numberOfThreadsForEachQueriedWord
resultsSimilarWordsType1 = [None] * numberOfThreadsForEachQueriedWord
resultsSimilarWordsType2 = [None] * numberOfThreadsForEachQueriedWord
resultsSimilarWordsType3 = [None] * numberOfThreadsForEachQueriedWord
resultsSimilarWordsType4 = [None] * numberOfThreadsForEachQueriedWord


dbListOfWords = ["bgu", "appel", "aah", "benzdioxdiazine", "doesNotExistsWord"]
numOfTypesOfRequests = len(dbListOfWords) # one for each different word

# exists - no matches
reqType0Word = "bgu"
listSimilarWordReq0 = []

# exists - 2 matches
reqType1Word = "appel"
listSimilarWordReq1 = ["apple","pepla"]

# exists - no matches
reqType2Word = "aah"
listSimilarWordReq2 = ["aha"]

# exists - 1 matches
reqType3Word = "benzdioxdiazine"
listSimilarWordReq3 = []

# does not exist - no matches
reqType4Word = "doesNotExistsWord"
listSimilarWordReq4 = []

threads = [None] * (numberOfThreadsForEachQueriedWord * numOfTypesOfRequests)

exitStatusCode = 0
totalNumberOfWordsInDb = 351075
totalRequests = 0
dbFileName = "words_clean.txt"

# first - start the server
serverProc = utils.StartServer("serverExe", dbFileName)

# wait for a moment while the server is booting
time.sleep(5)

resultsType0Index = 0
resultsType1Index = 0
resultsType2Index = 0
resultsType3Index = 0
resultsType4Index = 0

for i in range(len(threads)):
	reqType = (i % numOfTypesOfRequests)  # will resolve in [0-4]
	# similar?word=bgu	
	if (reqType == 0):
    	    	threads[i] = Thread(target=invokeGetSimilarWordsRequestMethod, args=(resultsSimilarWordsType0, resultsType0Index, reqType))
		resultsType0Index += 1
	# similar?word=appel	
	elif(reqType == 1):
    	    	threads[i] = Thread(target=invokeGetSimilarWordsRequestMethod, args=(resultsSimilarWordsType1, resultsType1Index, reqType))
		resultsType1Index += 1
	# similar?word=aah	
	elif(reqType == 2):
    	    	threads[i] = Thread(target=invokeGetSimilarWordsRequestMethod, args=(resultsSimilarWordsType2, resultsType2Index, reqType))
		resultsType2Index += 1
	# similar?word=benzdioxdiazine	
	elif(reqType == 3):
    	    	threads[i] = Thread(target=invokeGetSimilarWordsRequestMethod, args=(resultsSimilarWordsType3, resultsType3Index, reqType))
		resultsType3Index += 1
	# similar?word=doesNotExistsWord	
	elif(reqType == 4):
    	    	threads[i] = Thread(target=invokeGetSimilarWordsRequestMethod, args=(resultsSimilarWordsType4, resultsType4Index, reqType))
		resultsType4Index += 1
	threads[i].start()

# join all threads
for i in range(len(threads)):
    threads[i].join()

print ""
print ""
print colored("=====================================", "blue")
print colored("Done joining all " + str (len(threads)) + " threads", "blue")
print colored("=====================================", "blue")
print ""
print ""

# verify all GET similar?word=bgu requests were successfull
for i in range(len(resultsSimilarWordsType0)):
	if (False == utils.VerifyProperResponseForSimilarWordRequest(resultsSimilarWordsType0[i], 200, reqType0Word, listSimilarWordReq0)):
		exitStatusCode = 1

# verify all GET similar?word=appel requests were successfull
for i in range(len(resultsSimilarWordsType1)):
	if (False == utils.VerifyProperResponseForSimilarWordRequest(resultsSimilarWordsType1[i], 200, reqType1Word, listSimilarWordReq1)):
		exitStatusCode = 1

# verify all GET similar?word=aah requests were successfull
for i in range(len(resultsSimilarWordsType2)):
	if (False == utils.VerifyProperResponseForSimilarWordRequest(resultsSimilarWordsType2[i], 200, reqType2Word, listSimilarWordReq2)):
		exitStatusCode = 1

# verify all GET similar?word=benzdioxdiazine requests were successfull
for i in range(len(resultsSimilarWordsType3)):
	if (False == utils.VerifyProperResponseForSimilarWordRequest(resultsSimilarWordsType3[i], 200, reqType3Word, listSimilarWordReq3)):
		exitStatusCode = 1

# verify all GET similar?word=doesNotExistsWord requests were successfull
for i in range(len(resultsSimilarWordsType4)):
	if (False == utils.VerifyProperResponseForSimilarWordRequest(resultsSimilarWordsType4[i], 200, reqType4Word, listSimilarWordReq4)):
		exitStatusCode = 1

# finally, send GET stats request and verify the number of totalRequests is as excpected
response = utils.SendGetRequest("stats")

res = utils.VerifyProperResponseForStatsRequest(response, 200, totalNumberOfWordsInDb, numberOfThreadsForEachQueriedWord * numOfTypesOfRequests, 0)
if (res == False):
	print colored("got an invalid response for the stats request", "red")
	exitStatusCode = 1

print colored("Exiting Main Thread", "blue")

utils.ExitScript(exitStatusCode, serverProc)

