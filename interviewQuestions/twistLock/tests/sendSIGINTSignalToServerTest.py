import time

import utils


# ===========================================================================================================================================
# ===========================================================================================================================================

exitStatusCode = 0

# first - start the server
serverProc = utils.StartServer("serverExe")

# wait for a moment while the server is booting
time.sleep(1)

utils.ExitScript(exitStatusCode, serverProc)


