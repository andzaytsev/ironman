import time, urllib2

while True:
	time.sleep(0.5)
	print urllib2.urlopen("http://127.0.0.1:5000").read()
