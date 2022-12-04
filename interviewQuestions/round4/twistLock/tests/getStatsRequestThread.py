import threading
import time

import utils

# ---------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------

class GetStatsRequestThread (threading.Thread):
	def __init__(self, threadID, name, counter, delay):
      		threading.Thread.__init__(self)
      		self.threadID = threadID
      		self.name = name
      		self.counter = counter
		self.delay = delay
		self.request = "stats"
   	def run(self):
     		print "Starting " + self.name
      		self.sendGetStatsRequest()
      		print "Exiting " + self.name

	def sendGetStatsRequest(self):
		counter = self.counter   		
		while (counter > 0):
      			#time.sleep(self.delay)
      			print "sendGetStatsRequest- %s: %s" % (self.name, time.ctime(time.time()))
			print "sendGetStatsRequest - sending GET stats request number:" + str(self.counter - counter + 1)
			response = utils.SendGetRequest(self.request)
			if (utils.VerifyProperResponseForStatsRequest(response) == False):
				return counter
      			counter -= 1
		return counter





