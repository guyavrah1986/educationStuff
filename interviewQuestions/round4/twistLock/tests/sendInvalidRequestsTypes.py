import sys

import utils
import time

# ===========================================================================================================================================
# ===========================================================================================================================================

exitStatusCode = 0

# first - start the server
serverProc = utils.StartServer("serverExe")

# wait for a moment while the server is booting
time.sleep(1)

# --------------------------------
# send a PUT request to the server
# --------------------------------
response = utils.SendPutRequest("")

# we expect to recive an error code == 400 (Bad request)
if (response.status_code != 400):
	utils.ExitScript(1, serverProc)

# -----------------------------------
# send a DELETE request to the server
# -----------------------------------
response = utils.SendDeleteRequest("")

# we expect to recive an error code == 400 (Bad request)
if (response.status_code != 400):
	utils.ExitScript(1, serverProc)

# -----------------------------------
# send a POST request to the server
# -----------------------------------
response = utils.SendPostRequest("")

# we expect to recive an error code == 400 (Bad request)
if (response.status_code != 400):
	utils.ExitScript(1, serverProc)

# -----------------------------------
# send a HEAD request to the server
# -----------------------------------
response = utils.SendHeadRequest("")

# we expect to recive an error code == 400 (Bad request)
if (response.status_code != 400):
	utils.ExitScript(1, serverProc)


utils.ExitScript(exitStatusCode, serverProc)


