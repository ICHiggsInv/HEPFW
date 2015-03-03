#!/usr/bin/python

import os
import sys
import subprocess

if os.environ['HEPFWSYS'] is "":
  print "HEPFWSYS environment variable is not set... run appropriate thisHEPFW.(c)sh first!"
  sys.exit()

from optparse import OptionParser
parser = OptionParser()
parser.add_option('-j', dest="nJobs",    help='')
(options, args) = parser.parse_args()

currentPath = os.getcwd()

# Going to root of this HEPFW distributin
os.chdir(os.environ['HEPFWSYS'])

if options.nJobs:
  proc = subprocess.Popen(["make","all","-j",options.nJobs])
  proc.wait() # wait for the process to terminate otherwise the output is garbled
else:
  proc = subprocess.Popen(["make","all"])
  proc.wait() # wait for the process to terminate otherwise the output is garbled

# Returning to working directory
os.chdir(currentPath)