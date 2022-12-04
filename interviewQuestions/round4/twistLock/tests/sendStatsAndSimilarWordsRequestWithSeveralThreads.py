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
	if (reqType == 1):
		request = "similar?word=" + "cgb"
	elif (reqType == 2):
		request = "similar?word=" + "appel"
	elif (reqType == 3):
		request = "similar?word=" + "appll"
	results[index] = utils.SendGetRequest(request)
# ===========================================================================================================================================
# ===========================================================================================================================================

# globaL arrays:

numOfThreadsForStatsRequests = 2
numOfThreadsForSimilarWordRequestsType1 = 500
numOfThreadsForSimilarWordRequestsType2 = 500
numOfThreadsForSimilarWordRequestsType3 = 500
resultsStats = [None] * numOfThreadsForStatsRequests
resultsSimilarWordsType1 = [None] * numOfThreadsForSimilarWordRequestsType1
resultsSimilarWordsType2 = [None] * numOfThreadsForSimilarWordRequestsType2
resultsSimilarWordsType3 = [None] * numOfThreadsForSimilarWordRequestsType3

numOfTypesOfRequests = 3

dbListOfWords = ["a", "aa", "aah", "apple", "appel", "appll", "bgu", "bgc", "bgt", "cgb", "d", "pelpa", "gbcd"]

exitStatusCode = 0
totalNumberOfWords = 13

reqType1Word = "cgb"
listSimilarWordReq1 = ["bgc"]

reqType2Word = "appel"
listSimilarWordReq2 = ["apple", "pelpa"]

reqType3Word = "appll"
listSimilarWordReq3 = []

threads = [None] * (numOfThreadsForSimilarWordRequestsType1 + numOfThreadsForSimilarWordRequestsType2 + numOfThreadsForSimilarWordRequestsType3) # + numOfThreadsForStatsRequests)

# first - start the server
serverProc = utils.StartServer("serverExe")

# wait for a moment while the server is booting
time.sleep(1)

resultsStatsIndex = 0
resultsType1Index = 0
resultsType2Index = 0
resultsType3Index = 0

for i in range(len(threads)):
	reqType = (i % numOfTypesOfRequests) + 1  # will resolve in either [1,2,3]
	if (reqType == 0):
    		threads[i] = Thread(target=invokeGetStatsRequestMethod, args=(resultsStats, resultsStatsIndex))
		resultsStatsIndex += 1
	# similar?word=cgb	
	elif (reqType == 1):
    	    	threads[i] = Thread(target=invokeGetSimilarWordsRequestMethod, args=(resultsSimilarWordsType1, resultsType1Index, reqType))
		resultsType1Index += 1
	# similar?word=appel	
	elif(reqType == 2):
    	    	threads[i] = Thread(target=invokeGetSimilarWordsRequestMethod, args=(resultsSimilarWordsType2, resultsType2Index, reqType))
		resultsType2Index += 1
	# similar?word=appll	
	elif(reqType == 3):
    	    	threads[i] = Thread(target=invokeGetSimilarWordsRequestMethod, args=(resultsSimilarWordsType3, resultsType3Index, reqType))
		resultsType3Index += 1
	threads[i].start()

# join all threads
for i in range(len(threads)):
    threads[i].join()

print ""
print ""
print colored("Done joining all " + str (len(threads)) + " threads", "blue")

'''
# verify all GET stats requests were successfull
for i in range(len(resultsStats)):
	if (False == utils.VerifyProperResponseForStatsRequest(resultsStats[i], 200, totalNumberOfWords, (i * (numOfTypesOfRequests - 1)), 0)):
		exitStatusCode = 1
'''

# verify all GET similar?word=cgb requests were successfull
for i in range(len(resultsSimilarWordsType1)):
	if (False == utils.VerifyProperResponseForSimilarWordRequest(resultsSimilarWordsType1[i], 200, reqType1Word, listSimilarWordReq1)):
		exitStatusCode = 1

# verify all GET similar?word=appel requests were successfull
for i in range(len(resultsSimilarWordsType2)):
	if (False == utils.VerifyProperResponseForSimilarWordRequest(resultsSimilarWordsType2[i], 200, reqType2Word, listSimilarWordReq2)):
		exitStatusCode = 1

# verify all GET similar?word=appll requests were successfull
for i in range(len(resultsSimilarWordsType3)):
	if (False == utils.VerifyProperResponseForSimilarWordRequest(resultsSimilarWordsType3[i], 200, reqType3Word, listSimilarWordReq3)):
		exitStatusCode = 1

# finally, send GET stats request and verify the number of totalRequests is as excpected
response = utils.SendGetRequest("stats")

res = utils.VerifyProperResponseForStatsRequest(response, 200, totalNumberOfWords, numOfThreadsForSimilarWordRequestsType1 + numOfThreadsForSimilarWordRequestsType2 + numOfThreadsForSimilarWordRequestsType3, 0)
if (res == False):
	exitStatusCode = 1

print colored("Exiting Main Thread", "blue")

utils.ExitScript(exitStatusCode, serverProc)

