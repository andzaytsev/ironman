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
                os.dup2(sys.stdout.fileno(), 1)
                os.execv("./iman-data", ["./iman-data"])
	else:
		app.run()
