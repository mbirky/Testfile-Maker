#! python
# -*- mode: bash; tab-width: 4; -*-
# vi:ts=4 noexpandtab autoindent

import time
import os

class Timer(object):
	def __init__(self, verbose=False):
		self.verbose = verbose

	def __enter__(self):
		self.start = time.time()
		return self

	def __exit__(self, *args):
		self.end = time.time()
		self.secs = self.end - self.start
		self.msecs = self.secs * 1000  # millisecs
		if self.verbose:
			print 'elapsed time: %f ms' % self.msecs

def formatMin(min):
	if min < 10:
		return "0%s" % min
	return str(min)


outputFile = open('performance_output.txt', 'a')

currentTime = "%s:%s\n" % (str(time.localtime().tm_hour), formatMin(time.localtime().tm_min))
outputFile.write(currentTime)

with Timer() as t:
	os.system('../testfile_maker -s 1k')
outputFile.write("=> 1k elapsed: %s ms\n" % t.msecs)

with Timer() as t:
	os.system('../testfile_maker -s 1m')
outputFile.write("=> 1m elapsed: %s ms\n" % t.msecs)

with Timer() as t:
	os.system('../testfile_maker -s 1g')
outputFile.write("=> 1g elapsed: %s ms\n" % t.msecs)
