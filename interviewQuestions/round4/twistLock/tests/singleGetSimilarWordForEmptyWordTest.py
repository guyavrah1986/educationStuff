import time
from termcolor import colored
import json

import utils

# ===========================================================================================================================================
# ===========================================================================================================================================

exitStatusCode = 0
totalNumberOfWordsInDb = 351075
totalRequests = 0
dbFileName = "words_clean.txt"

# first - start the server
serverProc = utils.StartServer("serverExe", dbFileName)

# wait for a moment while the server is booting
time.sleep(5)

# send similar word request to the server
queryWord = ""
response = utils.SendGetRequest("similar?word=" + queryWord)

similarWordsList = [] # empty list

isValidResponse = utils.VerifyProperResponseForSimilarWordRequest(response, 200, queryWord, similarWordsList)

if (isValidResponse == False):
	exitStatusCode = 1
	jsonObj = json.loads(response.content)
	print colored("tests::singleGetSimilarWordForWordThatDoesNotExistsTest - got an invalid response", "red")
 	print colored(jsonObj, "red")
	print colored("tests::singleGetSimilarWordForWordThatDoesNotExistsTest - exiting with exit status code:" + str(exitStatusCode), "red")
	utils.ExitScript(exitStatusCode, serverProc)

totalRequests = totalRequests + 1

# send stats request to the server
response = utils.SendGetRequest("stats")

isValidResponse = utils.VerifyProperResponseForStatsRequest(response, 200, totalNumberOfWordsInDb, 1, 0)

if (isValidResponse == False):
	exitStatusCode = 1
	jsonObj = json.loads(response.content)
	print colored("tests::singleGetSimilarWordForWordThatDoesNotExistsTest - got an invalid response", "red")
 	print colored(jsonObj, "red")
	print colored("tests::singleGetSimilarWordForWordThatDoesNotExistsTest - exiting with exit status code:" + str(exitStatusCode), "red")
	utils.ExitScript(exitStatusCode, serverProc)

utils.ExitScript(exitStatusCode, serverProc)




