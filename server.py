from flask import Flask
app = Flask(__name__)
import random
import os
import sys, time

pipeout, pipein = os.pipe()

pipeout = os.fdopen(pipeout, 'r')

@app.route("/")
def hello():
    return pipeout.readline()


if __name__ == "__main__":
	if os.fork() == 0:
		old_stdout = sys.stdout
		sys.stdout = os.fdopen(pipein, 'w')
		os.system("./iman-data")
		# while True:  try to use this
		# 	time.sleep(5)
		# 	print random.randint(0, 10)
		# 	sys.stdout.flush()
	else:
		app.run()
