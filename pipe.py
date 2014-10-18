import os
import random
import time
import subprocess
import sys

cmd = ["./d"]

def close():
	# os.close(pipeout)
	# os.close(pipein)
	pass


def readLine(pipeout):
	return pipeout.readline()

def writeLine(pipein):
	time.sleep(0.5)
	os.write(pipeout, str(random.randint(0, 100))+"\n")

if __name__ == '__main__':
	pipein, pipeout = os.pipe()
	# if os.fork() == 0:
	# 	# subprocess.Popen(cmd, stderr = pipeout)
	# 	for i in xrange(0, 100):
	# 		writeLine(pipein)
	# 	close()
	# else:
	# 	pipeout = os.fdopen(pipeout)
	# 	for i in xrange(0, 100):
	# 		#pass
	# 		print readLine(pipeout)
	# 	close()
	p = subprocess.Popen(cmd, shell=True ,stdout=subprocess.PIPE)
	# Send input to p.
	# Now start grabbing output.
	stdout = []
	while True:
		line = p.stdout.readline()
		stdout.append(line)
		print line[:-1]
		if line == '' and p.poll() != None:
			break