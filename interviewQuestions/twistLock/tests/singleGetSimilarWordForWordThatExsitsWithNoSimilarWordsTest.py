import time
from termcolor import colored
import json

import utils

# ===========================================================================================================================================
# ===========================================================================================================================================

exitStatusCode = 0
totalNumberOfWordsInDb = 13
totalRequests = 0

# first - start the server
serverProc = utils.StartServer("serverExe")

# wait for a moment while the server is booting
time.sleep(1)

# send similar word request to the server
queryWord = "appll"
response = utils.SendGetRequest("similar?word=" + queryWord)

similarWordsList = [] # empty list

isValidResponse = utils.VerifyProperResponseForSimilarWordRequest(response, 200, queryWord, similarWordsList)

if (isValidResponse == False):
	exitStatusCode = 1
	jsonObj = json.loads(response.content)
	print colored("tests::singleGetSimilarWordForWordThatExistsWithNoSimilarWordsTest - got an invalid response", "red")
 	print colored(jsonObj, "red")
	print colored("tests::singleGetSimilarWordForWordThatExistsWithNoSimilarWordsTest - exiting with exit status code:" + str(exitStatusCode), "red")
	utils.ExitScript(exitStatusCode, serverProc)

# if we got here - the request was valid - so increment the counter value.
totalRequests = totalRequests + 1

# send stats request to the server
response = utils.SendGetRequest("stats")

isValidResponse = utils.VerifyProperResponseForStatsRequest(response, 200, totalNumberOfWordsInDb, totalRequests, 0)

if (isValidResponse == False):
	exitStatusCode = 1
	jsonObj = json.loads(response.content)
	print colored("tests::singleGetSimilarWordForWordThatExistsWithNoSimilarWordsTest - got an invalid response", "red")
 	print colored(jsonObj, "red")
	print colored("tests::singleGetSimilarWordForWordThatExistsWithNoSimilarWordsTest - exiting with exit status code:" + str(exitStatusCode), "red")
	utils.ExitScript(exitStatusCode, serverProc)

utils.ExitScript(exitStatusCode, serverProc)




