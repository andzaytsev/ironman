import os
import random


def close():
	# os.close(pipeout)
	# os.close(pipein)
	pass


def readLine(pipein):
	return pipein.readline()

def writeLine(pipeout):
	os.write(pipeout, str(random.randint(0, 100))+"\n")

if __name__ == '__main__':
	pipein, pipeout = os.pipe()
	if os.fork() == 0:
		for i in xrange(0, 100):
			writeLine(pipeout)
		close()
	else:
		pipein = os.fdopen(pipein)
		for i in xrange(0, 100):
			#pass
			print readLine(pipein)
		close()
