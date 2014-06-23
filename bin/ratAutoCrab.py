#!/usr/bin/python

import os
import sys
import math
import subprocess
import argparse
import time
import collections
import tempfile

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
def runCrabStatus(dirName,verbose,logFile):

  print "#### [ratAutoCrab.py:] Running CRAB status..."

  outJobs = []
  startJobs=False

  outF = tempfile.TemporaryFile() 
  errF = tempfile.TemporaryFile() 

  proc = subprocess.Popen(["crab","-status","-c",dirName], stdout=outF, stderr=errF)  
  proc.wait() # wait for the process to terminate otherwise the output is garbled
  
  outF.seek(0) # rewind to the beginning of the file
  fileContent = outF.read()
  
  outF.close()
  errF.close()
  
  if verbose: print fileContent
  logFile.write(fileContent)  
  out=fileContent.split('\n')
  
  for line in out:
  
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

  #for j in outJobs:
    #print "job id:",j.number," end:",j.end," status:",j.status," action:",j.action

  return outJobs

#_________________________________________________________
def runCrabGet(dirName,verbose,logFile):

  print "#### [ratAutoCrab.py:] Running CRAB get..."
  
  outF = tempfile.TemporaryFile() 
  errF = tempfile.TemporaryFile() 

  proc = subprocess.Popen(["crab","-get","-c",dirName], stdout=outF, stderr=errF)
  proc.wait() # wait for the process to terminate otherwise the output is garbled
  
  outF.seek(0) # rewind to the beginning of the file
  fileContent = outF.read()
  
  outF.close()
  errF.close()
  
  if verbose: print fileContent
  logFile.write(fileContent)  
  
#_________________________________________________________
def runCrabKill(dirName,jobs,verbose,logFile):

  print "#### [ratAutoCrab.py:] Running CRAB kill..."
  
  outF = tempfile.TemporaryFile() 
  errF = tempfile.TemporaryFile() 

  proc = subprocess.Popen(["crab","-kill",",".join(jobs),"-c",dirName], stdout=outF, stderr=errF)
  proc.wait() # wait for the process to terminate otherwise the output is garbled
  
  outF.seek(0) # rewind to the beginning of the file
  fileContent = outF.read()
  
  outF.close()
  errF.close()
  
  if verbose: print fileContent
  logFile.write(fileContent)  
  
#_________________________________________________________
def runCrabResubmit(dirName,jobs,verbose,logFile):

  print "#### [ratAutoCrab.py:] Running CRAB resubmit..."
  
  outF = tempfile.TemporaryFile() 
  errF = tempfile.TemporaryFile() 

  proc = subprocess.Popen(["crab","-resubmit",",".join(jobs),"-c",dirName], stdout=outF, stderr=errF)
  proc.wait() # wait for the process to terminate otherwise the output is garbled
  
  outF.seek(0) # rewind to the beginning of the file
  fileContent = outF.read()
  
  outF.close()
  errF.close()
  
  if verbose: print fileContent
  logFile.write(fileContent)
  
#_________________________________________________________
def needCrabGet(iJobs):
  
  print "#### [ratAutoCrab.py:] Checking if we need to do CRAB get..."
  
  out = False
  
  for j in iJobs:    
    if j.status=='Done' and j.action=='Terminated':
      print "#### [ratAutoCrab.py:] Found jobs that need retrieving!"
      out = True
      break

  return out

#_________________________________________________________
def getJobsKill(iJobs,logs):
  
  print "#### [ratAutoCrab.py:] Checking if we need to kill jobs..."

  out = []

  jobsStatus = collections.defaultdict(int)

  for j in iJobs:    
    if j.status=='Cancelled' and j.action=='SubSuccess':
      jobsStatus['Cancelled']+=1
      logs.write("Found job "+j.number+" cancelled!\n")
      print "#### [ratAutoCrab.py:] Found a cancelled job!"
      out.append(j.number)

  return out

#_________________________________________________________
def getJobsResubmit(iJobs,logs):
  
  print "#### [ratAutoCrab.py:] Checking if we need to resubmit jobs..."

  out = []
  
  jobsStatus = collections.defaultdict(int)
  
  for j in iJobs:    
    if j.status=='Retrieved' and j.action=='Cleared' and j.exeExitCode=='0' and j.jobExitCode=='0':
      jobsStatus[0]+=1
      logs.write("Found job "+j.number+" with code 0: Done\n")
    elif  j.status=='Submitted' and j.action=='SubSuccess':
      jobsStatus['Submitted']+=1 
      logs.write("Found job "+j.number+" submitted!\n")
    elif  j.status=='Running' and j.action=='SubSuccess':
      jobsStatus['Running']+=1 
      logs.write("Found job "+j.number+" running!\n") 

    elif j.status=='Aborted' and j.action=='Aborted':
      jobsStatus['Aborted']+=1 
      logs.write("Found job "+j.number+" aborted!\n")
      out.append(j.number)
    elif j.status=='Cancelled' and j.action=='KillSuccess':
      jobsStatus['Cancelled']+=1 
      logs.write("Found job "+j.number+" cancelled!\n")
      out.append(j.number)

    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='50664':
      jobsStatus[50664]+=1
      logs.write("Found job "+j.number+" with code 50664: Application terminated by wrapper because using too much Wall Clock time\n")
      out.append(j.number)                        
    elif j.status=='Retrieved' and j.action=='Cleared' and (j.exeExitCode=='50669' or j.jobExitCode=='50669'):
      jobsStatus[50669]+=1
      logs.write("Found job "+j.number+" with code 50669: Application terminated by wrapper for not defined reason\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and (j.exeExitCode=='50700' or j.jobExitCode=='50700'):
      jobsStatus[50700]+=1
      logs.write("Found job "+j.number+" with code 50700: Job Wrapper did not produce any usable output file\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='8021':
      jobsStatus[8021]+=1
      logs.write("Found job "+j.number+" with code 8021: FileReadError (May be a site error)\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='8022':
      jobsStatus[8022]+=1
      logs.write("Found job "+j.number+" with code 8022: FatalRootError\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='8028':
      jobsStatus[8028]+=1
      logs.write("Found job "+j.number+" with code 8028: FileOpenError with fallback!\n")
      out.append(j.number)         
    else:
      logs.write("Found job "+j.number+" with unknown code\n")
      jobsStatus['Unknown']+=1

  print "#### [ratAutoCrab.py:] Job summary:"
  logs.write("Job summary:\n")
  for k in jobsStatus.keys():
    txt = "=> Status: "+str(k)+" - "+str(jobsStatus[k])+" jobs"
    logs.write(txt+"\n")
    print "#### [ratAutoCrab.py:]",txt

  return out

#_________________________________________________________
def processJobs(dirName,currentTime,verbose):

  print ""  
  print ""
  print "#### [ratAutoCrab.py:] *** Parameters ***"
  print "#### [ratAutoCrab.py:] CRAB Input directory : ", dirName
  print "#### [ratAutoCrab.py:] ******************"
  
  # Opening log file
  logCrab     = open('ratAutoCrab_'+dirName+'_'+currentTime+'.log', 'w')
  logSummmary = open('ratAutoCrab_'+dirName+'_'+currentTime+"_summary"+'.log', 'w')
  
  vJobs = runCrabStatus(dirName,verbose,logCrab)

  while needCrabGet(vJobs):
    runCrabGet(dirName,verbose,logCrab)
    vJobs = runCrabStatus(dirName,verbose,logCrab)
    
  vJobsKill     = getJobsKill    (vJobs,logSummmary)
  vJobsResubmit = getJobsResubmit(vJobs,logSummmary)

  if len(vJobsKill)>0:
    print "#### [ratAutoCrab.py:] Found",len(vJobsResubmit),"jobs to be killed..."
    runCrabKill(dirName,vJobsKill,verbose,logCrab)
  if len(vJobsResubmit)>0:
    print "#### [ratAutoCrab.py:] Found",len(vJobsResubmit),"jobs to be resubmitted..."
    runCrabResubmit(dirName,vJobsResubmit,verbose,logCrab)
    print "#### [ratAutoCrab.py:] Done!"
  else:
    print "#### [ratAutoCrab.py:] Nothing needs to be resubmitted."


#_________________________________________________________
# Main code
#_________________________________________________________

parser = argparse.ArgumentParser(description='Automatically deal of CRAB jobs maintenance: check for finished jobs, retrieve outputs and resubmit failed jobs.')
parser.add_argument('dirs', metavar='DIR', type=str, nargs='+',help='Target CRAB directories')
parser.add_argument("-v", "--verbose", help="Show CRAB output.",action="store_true")
args = parser.parse_args()

currentTime = time.strftime("%Y%m%d_%H%M%S")

for arg in args.dirs:
  processJobs(arg,currentTime,args.verbose)






    


