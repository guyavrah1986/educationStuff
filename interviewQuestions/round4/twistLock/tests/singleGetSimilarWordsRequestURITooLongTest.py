import time
from termcolor import colored
import json
import sys

import utils

# ===========================================================================================================================================
# ===========================================================================================================================================

exitStatusCode = 0
totalNumberOfWordsInDb = 351075
totalRequests = 0
dbFileName = "words_clean.txt"
maxURILen = 2041 # defined in the source code as TS_MAX_QUERY_STRING_LEN (serverUtilities.h file)
responseStatusCode = 414

# first - start the server
serverProc = utils.StartServer("serverExe", dbFileName)

# wait for a moment while the server is booting
time.sleep(5)

# send a similar word request which has an invalid URI (too long > 20)
queryWord = utils.randomWord(maxURILen)
response = utils.SendGetRequest("similar?word=" + queryWord)

# verify correct error code
if (response.status_code != responseStatusCode):
	jsonObj = json.loads(response.content)
	print colored("tests::singleGetStatsRequestURITooLongTest - got an invalid response", "red")
 	print colored(jsonObj, "red")
	print colored("tests::singleGetStatsRequestURITooLongTest - exiting with exit status code:" + str(exitStatusCode), "red")
	utils.ExitScript(1, serverProc)

utils.ExitScript(exitStatusCode, serverProc)





