#!/usr/bin/python

import os
import sys
import math
import subprocess
from optparse import OptionParser

class job:
  number      = 0
  endStatus   = ""
  action      = ""
  exeExitCode = ""
  jobExitCode = ""
  host        = "" 

vJobs = []

target = sys.argv[2]

parser = OptionParser()
parser.add_option("-c", "--continue", dest="directory",
                  help="CRAB directory", metavar="DIR")

(options, args) = parser.parse_args()

if not options.directory:
  parser.error("Need to supply an input directory!")

print "*** Parameters ***"
print "Input directory         : ", options.directory

cmd = subprocess.Popen(["crab","-status","-c",target], stdout=subprocess.PIPE, stderr=subprocess.PIPE,shell=False)
stdout, stderr = cmd.communicate()

stdout=stdout.split('\n')
stderr=stderr.split('\n')

startJobs=False

for i in stdout:

  if startJobs:
    
    if i.find("-----") is not -1:
      continue
    
    if i is "":
      startJobs=False
      continue
    
    print i
    
    data=i.split()
    
    x = job()
    x.number      = data[0]
    x.endStatus   = data[1]
    x.action      = data[2]
    if len(data)>3: x.exeExitCode = data[3]
    if len(data)>4: x.jobExitCode = data[4]
    if len(data)>5: x.host        = data[5]
    vJobs.append(x)  
  
  if i.find("ID") is not -1:
    startJobs=True
    

for j in vJobs:
  print "job ID:",j.number," endStatus:",j.endStatus

