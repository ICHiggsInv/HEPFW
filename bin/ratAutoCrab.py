#!/usr/bin/python

import os
import sys
import math
import subprocess
from optparse import OptionParser
import time

#_________________________________________________________
class job:
  number      = 0
  end         = ""
  status      = ""
  action      = ""
  exeExitCode = ""
  jobExitCode = ""
  host        = "" 

#_________________________________________________________
def runCrabStatus(dirName,logFile):

  print "Running CRAB status..."

  outJobs = []
  
  startJobs=False

  proc = subprocess.Popen(["crab","-status","-c",dirName], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
  for line in proc.stdout:
    sys.stdout.write(line)
    logFile.write(line)
  
    if startJobs:
    
      if line.find("-----") is not -1:
        continue
    
      if line.rstrip() is '':
        startJobs=False
        continue
    
      data=line.split()
    
      x = job()
      x.number      = data[0]
      x.end         = data[1]
      x.status      = data[2]
      x.action      = data[3]
      if len(data)>4: x.exeExitCode = data[4]
      if len(data)>5: x.jobExitCode = data[5]
      if len(data)>6: x.host        = data[6]
      outJobs.append(x)
  
    if line.find("ID") is not -1:
      startJobs=True
  proc.wait()

  for j in outJobs:
    print "job id:",j.number," end:",j.end," status:",j.status," action:",j.action

  return outJobs

#_________________________________________________________
def runCrabGet(dirName,logFile):

  print "Running CRAB get..."

  proc = subprocess.Popen(["crab","-get","-c",dirName], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
  for line in proc.stdout:
    sys.stdout.write(line)
    logFile.write(line)
  proc.wait()
  

#_________________________________________________________
def runCrabResubmit(dirName,jobs,logFile):

  print "Running CRAB resubmit..."
  
  proc = subprocess.Popen(["crab","-resubmit",",".join(vJobsResubmit),"-c",dirName], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
  for line in proc.stdout:
    sys.stdout.write(line)
    logFile.write(line)
  proc.wait()
  
#_________________________________________________________
def needCrabGet(iJobs):
  
  print "Checking if we need to do CRAB get..."
  
  out = False
  
  for j in iJobs:    
    if j.status=='Done' and j.action=='Terminated':
      print "Found one jobs that needs retrieving!"
      out = True
      break

  return out

#_________________________________________________________
def getJobsResubmit(iJobs):
  
  print "Checking if we need to do CRAB get..."
  
  out = []
  
  for j in iJobs:    
    if j.status=='Aborted' and j.action=='Aborted':
      print "Found Aborted job!"
      out.append(j.number)
      break

  return out

#_________________________________________________________
target = sys.argv[1]

print "*** Parameters ***"
print "Input directory         : ", target

# Opening log file
log = open('ratAutoCrab_'+target+'_'+time.strftime("%Y%m%d_%H%M%S")+'.log', 'w')

vJobs = runCrabStatus(target,log)

while needCrabGet(vJobs):
  runCrabGet(target,log)
  vJobs = runCrabStatus(target,log)

vJobsResubmit = getJobsResubmit(vJobs)

if len(vJobsResubmit)>0:
  print "Found",len(vJobsResubmit),"jobs to be resubmitted..."
  runCrabResubmit(target,vJobsResubmit,log)
  print "Done!"
else:
  print "No operation to be done..,"


    


