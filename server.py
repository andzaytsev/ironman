from flask import Flask
app = Flask(__name__)
import random
import os, threading
import sys, time, signal

pipeout, pipein = os.pipe()

pipeout = os.fdopen(pipeout, 'r')

lastline = ""

@app.route("/")
def hello():
	global lastline
	return lastline

def getlastLine():
	while True:
		global lastline
		lastline = pipeout.readline()


if __name__ == "__main__":
	child_id = os.fork()
	if child_id == 0:
		old_stdout = sys.stdout
		sys.stdout = os.fdopen(pipein, 'w')
		os.dup2(sys.stdout.fileno(), 1)
		os.execv("./iman-data", ["./iman-data"])
	else:
		def signal_handler(signals, frame):
			print "KILL CHILD %d"%child_id
			os.kill(child_id, signal.SIGINT)
			sys.exit(0)
		signal.signal(signal.SIGINT, signal_handler)
		thread = threading.Thread(target=getlastLine, args=())
		thread.start()
		app.run()
