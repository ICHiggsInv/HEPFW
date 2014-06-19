#!/usr/bin/python

import os
import sys
import math
import subprocess
from optparse import OptionParser

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
def runCrabStatus(dirName):

  print "Running CRAB status..."

  outJobs = []

  logfile = open('logfile', 'w')
  proc = subprocess.Popen(["crab","-status","-c",dirName], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  for line in proc.stdout:
    sys.stdout.write(line)
    logfile.write(line)
  proc.wait()

  stdout, stderr = proc.communicate()

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
    
      data=i.split()
    
      x = job()
      x.number      = data[0]
      x.end         = data[1]
      x.status      = data[2]
      x.action      = data[3]
      if len(data)>4: x.exeExitCode = data[4]
      if len(data)>5: x.jobExitCode = data[5]
      if len(data)>6: x.host        = data[6]
      outJobs.append(x)
  
    if i.find("ID") is not -1:
      startJobs=True

  for j in outJobs:
    print "job id:",j.number," end:",j.end," status:",j.status," action:",j.action

  return outJobs

#_________________________________________________________
def runCrabGet(dirName):

  print "Running CRAB get..."

  cmd = subprocess.Popen(["crab","-get","-c",dirName], stdout=subprocess.PIPE, stderr=subprocess.PIPE,shell=False)
  stdout, stderr = cmd.communicate()

#_________________________________________________________
def runCrabResubmit(dirName,jobs):

  print "Running CRAB resubmit..."

  cmd = subprocess.Popen(["crab","-resubmit",",".join(vJobsResubmit),"-c",dirName], stdout=subprocess.PIPE, stderr=subprocess.PIPE,shell=False)
  stdout, stderr = cmd.communicate()
  
#_________________________________________________________
def needCrabGet(iJobs):
  
  print "Checking if we need to do CRAB get..."
  
  out = False
  
  for j in iJobs:    
    if j.status=='Done' and j.action=='Terminated':
      print "Found one!"
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

vJobs = runCrabStatus(target)

while needCrabGet(vJobs):
  runCrabGet(target)
  vJobs = runCrabStatus(target)

vJobsResubmit = getJobsResubmit(vJobs)

if len(vJobsResubmit)>0:
  print "Found",len(vJobsResubmit),"jobs to be resubmitted..."
  runCrabResubmit(target,vJobsResubmit)
  print "Done!"
else:
  print "No operation to be done..,"


    


