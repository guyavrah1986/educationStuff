import os
import subprocess
import requests
import json
import sys
import signal
import time
import random
import string
from termcolor import colored

def StartServer(serverExeName, dbFileName = "words_clean_testing.txt"):

	cwd = os.getcwd()
	print colored("utils::StartServer - current working directory is:" + cwd, "blue")
	exeName = serverExeName
	exeFolderFullPath = cwd + "/build/build/"
	dbFileFullPath = cwd + "/textFiles/" + dbFileName
	numOfWorkerThreads = 2
	cmd = exeFolderFullPath + exeName + " " + dbFileFullPath
	print colored("utils::StartServer - running server with DB file:" + dbFileFullPath + " and " + str(numOfWorkerThreads) + " worker threads", "blue")
	serverProc = subprocess.Popen([exeFolderFullPath + exeName, dbFileFullPath, str(numOfWorkerThreads)])
	return serverProc

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def KillServer(serverProcNumber):
	serverProc.kill()

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def SendGetRequest(request):
	return requests.get("http://127.0.0.1:8000/api/v1/" + request)

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def SendPutRequest(request):
	return requests.put('http://127.0.0.1:8000/put')

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def SendDeleteRequest(request):
	return requests.delete("http://127.0.0.1:8000/delete")

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def SendPostRequest(request):
	return requests.post("http://127.0.0.1:8000/post")

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def SendHeadRequest(request):
	return requests.get("http://127.0.0.1:8000/head")

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def SendOptionsRequest(request):
	return requests.get("http://127.0.0.1:8000/options")

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def VerifyProperResponseForStatsRequest(response, statusCode, totalNumberWords, totalRequests, avgProcessingTimeNsPrev = 0):
	# verify proper status code
	if (response.status_code != statusCode):
		return False

	# extract the JSON object from the response content
	jsonObj = json.loads(response.content)

	# verify total number of words
	if (jsonObj["totalWords"] != totalNumberWords):
		return False

	# verify total request
	if (jsonObj["totalRequests"] != totalRequests):
		return False

	# verify avgProcessingTimeNs
	'''
	if (jsonObj["avgProcessingTimeNs"] < avgProcessingTimeNsPrev):
		return False
	'''

	print colored(jsonObj, "blue")
	# example for a valid output: {"totalWords":13, "totalRequests":0, "avgProcessingTimeNs":0}	
	return True

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def VerifyProperResponseForSimilarWordRequest(response, statusCode, queryWord, listOfMatchedWords):
	# verify proper status code
	if (response.status_code != statusCode):
		return False

	# extract the similar words list
	jsonObj = json.loads(response.content)
	returnedSimilarWordsList = jsonObj["similar"]
	print colored("utils::VerifyProperResponseForSimilarWordRequest - got the following similar words:", "blue")
	print returnedSimilarWordsList
	if (comp(listOfMatchedWords, returnedSimilarWordsList)):
		if (queryWord not in returnedSimilarWordsList):
			return True
		else:
			print colored("utils::VerifyProperResponseForSimilarWordRequest - the queried word in WITHIN the similar word list returned from the server", "red")
			return False	
	else:
		print colored("utils::VerifyProperResponseForSimilarWordRequest - the similar words returned from the server is not valid:", "red")
		return False

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def GetAvgProcessingTimeFromResponse(response):
	jsonObj = json.loads(response.content)
	return jsonObj["avgProcessingTimeNs"]

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def ExitScript(exitCode, serverProc):
	# kill the server process
	os.kill(serverProc.pid, signal.SIGINT)
	sys.exit(exitCode)

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def ExecuteSeveralValidGetRequestsInParallel(numOfRequestsToSend, reuestType, delayBetweenEachRequest, word):
	count = 0
   	while count < numOfRequestsToSend:
      		time.sleep(delayBetweenEachRequest)
      		count += 1
		# Stats request
		if (reuestType == 1):
			SendGetRequest(word)
		# SimilarWords request
		elif (reuestType == 2):
			print colored("utils::ExecuteSeveralValidGetRequestsInParallel - SimilarWords request type", "blue")
		else:
			print colored("utils::ExecuteSeveralValidGetRequestsInParallel - invalid request type, aborting...", "blue")
			return -1

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def ReadAllWordsFromFileIntoList(dbFileName):
    cwd = os.getcwd()
    listOfWordsInFile = []
    dbFileFullPath = cwd + "/textFiles/" + dbFileName
    print colored("utils::ReadAllWordsFromFileIntoList - about to open file:" + dbFileFullPath, "blue")
    with open(dbFileFullPath) as f:
        for line in f:
            listOfWordsInFile.append(line)
           
    print colored("utils::ReadAllWordsFromFileIntoList - done reading " + str(len(listOfWordsInFile)) + " words from file", "blue")
    return listOfWordsInFile     
   
# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def ComposeUri(apiPrefix, word):
	uriToSend = apiPrefix + word
	return (uriToSend)
	
# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def comp(list1, list2):
	for val in list1:
		if val not in list2:
			return False
	return True

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def vaidateAvgProcessingTime(prevTimeStamp, currTimeStamp):
	diff = currTimeStamp - prevTimeStamp

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

def randomWord(length):
   letters = string.ascii_lowercase
   return ''.join(random.choice(letters) for i in range(length))


