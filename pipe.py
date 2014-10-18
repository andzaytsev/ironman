import os
import random
import time
import sys

def readLine(pipeout):
	return pipeout.readline()

def writeLine(pipein):
	time.sleep(0.5)
	os.write(pipeout, str(random.randint(0, 100))+"\n")

if __name__ == '__main__':
	pipeout, pipein = os.pipe()
        old_stdout = sys.stdout
        sys.stdout = os.fdopen(pipein, 'w')
	if os.fork() == 0: # child
                print 'hello'
        else: # parent
	 	pipeout = os.fdopen(pipeout, 'r')
                old_stdout.write(readLine(pipeout))
