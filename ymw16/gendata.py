#!/usr/bin/python
import sys
import os
import getopt
import string
import pyfits
import numpy
import math
import matplotlib.pyplot as plt
from optparse import OptionParser,OptionGroup
#in~/srclib/pylib/, one can modify the .bashrc PYTHONPATH to do the job
from astro import *

d=10;

for l in range(0,370,10):
	for b in range(-90, 100,10):
		cmdline="./NE2001 %f %f %f -1 | grep 'ModelDM' | awk \'{print $1}\'>> a.txt" % (l,b,d)
		print cmdline
		os.system(cmdline)
	cmdline="echo ZZZZ >> a.txt"
	os.system(cmdline)

	

