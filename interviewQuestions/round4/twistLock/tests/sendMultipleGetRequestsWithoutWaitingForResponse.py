import grequests
import time
from termcolor import colored
from tornado import ioloop, httpclient
import json

import utils

# ===========================================================================================================================================
# ===========================================================================================================================================

i = 0
numOfRequestSent = 0

def handleRequest(response):
    if (response.code != 200):
        '''
        print colored("sendMultipleGetRequestsWithoutWaitingForResponse::handleRequest - got an invalid response status code (!= 200)", "red")
        '''
    global i
    global numOfRequestSent
    numOfRequestSent += 1
    i -= 1
    if i == 0:
        ioloop.IOLoop.instance().stop()

def SendRequestOnceForEachWord(listOfUrisForWordsInDbFile):
    rs = (grequests.get(u, stream=False) for u in listOfUrisForWordsInDbFile)
    responses = grequests.map(rs)
    
    for response in responses:
        response.close()
    
    print colored("sendMultipleGetRequestsWithoutWaitingForResponse::SendRequestOnceForEachWord - done accumulating all responses", "blue")

def VerifyProperNumberOfRequests(totalNumberOfWordsInDb, totalRequests):
    response = utils.SendGetRequest("stats")
    isValidResponse = utils.VerifyProperResponseForStatsRequest(response, 200, totalNumberOfWordsInDb, totalRequests)

    if (isValidResponse == False):
        jsonObj = json.loads(response.content)
        print colored("sendMultipleGetRequestsWithoutWaitingForResponse::VerifyProperNumberOfRequests - got an invalid response", "red")
        print colored(jsonObj, "red")
        return False
    else:
        print colored("sendMultipleGetRequestsWithoutWaitingForResponse::VerifyProperNumberOfRequests - got valid response for the stats query", "blue")    
        return True    
# ===========================================================================================================================================
# ===========================================================================================================================================

start_time = time.time()
print colored("sendMultipleGetRequestsWithoutWaitingForResponse - start", "blue")
dbFileName = "words_clean.txt"
apiPrefix = "http://localhost:8000/api/v1/similar?word="
listOfWords = utils.ReadAllWordsFromFileIntoList(dbFileName)
nonExisitingWords = ["buba", "", "buli", "rotem" , "@@#@", "123", "!yytrytyt", "7", "==", "_rtee"]   


numOfRequestsToSend = 1000
counter = 0
badWordCounter = 10
badWordIndex = 0

''' Prepare URLs to send '''
listOfUrisForWordsInDbFile = []
for word in listOfWords:
    ''' Once in a while integrate non exsisting words as well '''
    if (counter % badWordCounter == 0):
        word = nonExisitingWords[badWordIndex]
        badWordIndex += 1
        if (badWordIndex == len(nonExisitingWords)):
            badWordIndex = 0
    uri = utils.ComposeUri(apiPrefix, word)
    '''# remove \n !! '''
    uri = uri.rstrip() 
    listOfUrisForWordsInDbFile.append(uri)
    
    counter += 1
    if (counter >= numOfRequestsToSend):
        break
       
print colored("sendMultipleGetRequestsWithoutWaitingForResponse - done composing URI for " + str(len(listOfUrisForWordsInDbFile)) + " words", "blue")

''' Send URLs '''
http_client = httpclient.AsyncHTTPClient()
for url in listOfUrisForWordsInDbFile:
    i += 1
    http_client.fetch(url.strip(), handleRequest, method='GET')
ioloop.IOLoop.instance().start()

''' Verify that the stats counter in the server is correct '''
res = VerifyProperNumberOfRequests(len(listOfWords), numOfRequestsToSend)
colorToPrint = "red"
if (res == True):
    colorToPrint = "blue"
    
print colored("sendMultipleGetRequestsWithoutWaitingForResponse - done sending " + str(numOfRequestSent) + " request", colorToPrint)
print colored("sendMultipleGetRequestsWithoutWaitingForResponse toook:" +  str(time.time() - start_time), colorToPrint) 
