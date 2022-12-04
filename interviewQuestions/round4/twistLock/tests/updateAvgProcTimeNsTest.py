import time

import utils

# ===========================================================================================================================================
# ===========================================================================================================================================

exitStatusCode = 0
numOfSuccessfullRequestsSentSoFar = 0
totalNumberOfWordsInDb = 13

serverProc = utils.StartServer("serverExe")

# wait for a moment while the server is booting
time.sleep(1)

# send first similar?word request
queryWord = "apple"
response = utils.SendGetRequest("similar?word=" + queryWord)

similarWordsList = ["appel", "pelpa"]

isValidResponse = utils.VerifyProperResponseForSimilarWordRequest(response, 200, queryWord, similarWordsList)

if (isValidResponse == False):
	utils.ExitScript(1, serverProc)

numOfSuccessfullRequestsSentSoFar = numOfSuccessfullRequestsSentSoFar + 1

# check that the number of request increase to 1 and that the avgProcessingTimeNs > 0
response = utils.SendGetRequest("stats")

isValidResponse = utils.VerifyProperResponseForStatsRequest(response, 200, totalNumberOfWordsInDb, numOfSuccessfullRequestsSentSoFar, 0)

# terminate test now if the response for the first request is not valid
if (isValidResponse == False):
	utils.ExitScript(1, serverProc)

# keep the previous request AvgProcessingTime
prevAvgProcessingTimeNs = utils.GetAvgProcessingTimeFromResponse(response)
			
# send second similar?word request
queryWord = "cgb"
response = utils.SendGetRequest("similar?word=" + queryWord)
similarWordsList = ["bgc"]

isValidResponse = utils.VerifyProperResponseForSimilarWordRequest(response, 200, queryWord, similarWordsList)

if (isValidResponse == False):
	utils.ExitScript(1, exitStatusCode)

numOfSuccessfullRequestsSentSoFar = numOfSuccessfullRequestsSentSoFar + 1

# check that the number of request increase to 2 and that the avgProcessingTimeNs > previous avgProcessingTimeNs
response = utils.SendGetRequest("stats")

isValidResponse = utils.VerifyProperResponseForStatsRequest(response, 200, totalNumberOfWordsInDb, numOfSuccessfullRequestsSentSoFar, prevAvgProcessingTimeNs)

# terminate test now if the response for the first request is not valid
if (isValidResponse == False):
	utils.ExitScript(1, serverProc)

utils.ExitScript(exitStatusCode, serverProc)

