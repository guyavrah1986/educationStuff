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
queryWord = "apple"
response = utils.SendGetRequest("similar?word=" + queryWord)

similarWordsList = ["appel", "pepla"]

isValidResponse = utils.VerifyProperResponseForSimilarWordRequest(response, 200, queryWord, similarWordsList)

if (isValidResponse == False):
	exitStatusCode = 1
	jsonObj = json.loads(response.content)
	print colored("tests::singleGetSimilarWordsRequestTest - got an invalid response", "red")
	print colored(jsonObj, "red")
	print colored("tests::singleGetSimilarWordsRequestTest - exiting with exit status code:" + str(exitStatusCode), "red")
	utils.ExitScript(exitStatusCode, serverProc)

# if we got here -- than the request was successful, update the counter
totalRequests = totalRequests + 1

# send a stats request to the server
response = utils.SendGetRequest("stats")

isValidResponse = utils.VerifyProperResponseForStatsRequest(response, 200, totalNumberOfWordsInDb, totalRequests)

if (isValidResponse == False):
	exitStatusCode = 1
	jsonObj = json.loads(response.content)
	print colored("tests::singleGetSimilarWordsRequestTest - got an invalid response", "red")
	print colored(jsonObj, "red")
	print colored("tests::singleGetSimilarWordsRequestTest - exiting with exit status code:" + str(exitStatusCode), "red")

utils.ExitScript(exitStatusCode, serverProc)




