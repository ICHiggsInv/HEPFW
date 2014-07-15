#!/usr/bin/python

import os
import io
import sys
import math
import subprocess
import argparse
import time
import collections
import tempfile
import json

#_________________________________________________________
class CRABTask:
  
  crabDir   = ""
  hasInfo   = False
  directory = ""
  nJobs     = 0
  status    = "Undefined"
  
  variables = dict()
  
  def __init__(self, iDirectory):
    print "In the constructor of CRABTask"
    self.crabDir = iDirectory
    if (os.path.isfile(iDirectory+"/autoCrab.info")):
      print "Found autoCrab.info"
      hasInfo=True

      with io.open(iDirectory+"/autoCrab.info", 'r', encoding='utf-8') as inFile:
        self.variables = json.load(inFile) 
        print repr(self.variables)
        
    else:
      print "Did not found autoCrab.info"
      self.variables['nJobs'] = 0

  def __enter__(self):
    return self

  def __del__(self):
    print "In the destructor of CRABTask"
    
    with io.open(self.crabDir+"/autoCrab.info", 'w', encoding='utf-8') as outFile:
      outFile.write(unicode(json.dumps(self.variables, ensure_ascii=False)))
    
    #print repr(json.dumps(self.variables))

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
def runCrabStatus(dirName,task,verbose,logFile):

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

  task.variables['nJobs'] = len(outJobs)

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
    elif  j.status=='Created' and j.action=='Created':
      jobsStatus['Created']+=1 
      logs.write("Found job "+j.number+" created!\n") 
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

    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='8001':
      jobsStatus[8001]+=1
      logs.write("Found job "+j.number+" with code 8001: "+getCrabErrorMessage(8001)+"\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='8002':
      jobsStatus[8002]+=1
      logs.write("Found job "+j.number+" with code 8002: "+getCrabErrorMessage(8002)+"\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='8021':
      jobsStatus[8021]+=1
      logs.write("Found job "+j.number+" with code 8021: "+getCrabErrorMessage(8021)+"\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='8022':
      jobsStatus[8022]+=1
      logs.write("Found job "+j.number+" with code 8022: "+getCrabErrorMessage(8022)+"\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='8028':
      jobsStatus[8028]+=1
      logs.write("Found job "+j.number+" with code 8028: "+getCrabErrorMessage(8028)+"\n")
      out.append(j.number)         
    elif j.status=='Retrieved' and j.action=='Cleared' and j.jobExitCode=='50664':
      jobsStatus[50664]+=1
      logs.write("Found job "+j.number+" with code 50664: "+getCrabErrorMessage(50664)+"\n")
      out.append(j.number)                        
    elif j.status=='Retrieved' and j.action=='Cleared' and (j.exeExitCode=='50669' or j.jobExitCode=='50669'):
      jobsStatus[50669]+=1
      logs.write("Found job "+j.number+" with code 50669: "+getCrabErrorMessage(50669)+"\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and (j.exeExitCode=='50700' or j.jobExitCode=='50700'):
      jobsStatus[50700]+=1
      logs.write("Found job "+j.number+" with code 50700: "+getCrabErrorMessage(50700)+"\n")
      out.append(j.number)
    elif j.status=='Retrieved' and j.action=='Cleared' and (j.exeExitCode=='50800' or j.jobExitCode=='50800'):
      jobsStatus[50800]+=1
      logs.write("#### WARNING #### Found job "+j.number+" with code 50800: "+getCrabErrorMessage(50800)+"\n")
      out.append(j.number)
    
    else:
      logs.write("Found job "+j.number+" with unknown code\n")
      jobsStatus['Unknown']+=1

  print "#### [ratAutoCrab.py:] Job summary:"
  logs.write("Job summary:\n")
  for k in sorted(jobsStatus):
    txt = str()
    if k=="Created" or k=="Submitted" or k=="Running" or k=="Aborted" or k=="Cancelled":
      txt = "=> {0:>5s} jobs with status {1:10s}".format(str(jobsStatus[k]),str(k))      
    else:
      txt = "=> {0:>5s} jobs with status {1:10s}: {2}".format(str(jobsStatus[k]),str(k),getCrabErrorMessage(k))

    logs.write(txt+"\n")
    print "#### [ratAutoCrab.py:]",txt

  return out

#_________________________________________________________
def getCrabErrorMessage(errorCode):

  errMsg = collections.defaultdict(int)

  errMsg[0] = "Done"

  # Error exit code of the cmsRun application itself - range 0-10000 (Exit codes in 1-512 are standard ones in Unix and indicate a CMSSW abort that the cmsRun did not catch as exception)
  errMsg[1] = "Hangup (POSIX)"
  errMsg[2] = "Interrupt (ANSI)"
  errMsg[3] = "unknown"
  errMsg[4] = "Illegal instruction (ANSI)"
  errMsg[5] = "Trace trap (POSIX)"
  errMsg[6] = "Abort (ANSI) or IOT trap (4.2BSD)"
  errMsg[7] = "BUS error (4.2BSD)"
  errMsg[8] = "Floating point exception (ANSI)"
  errMsg[9] = "killed, unblockable (POSIX) kill -9"
  errMsg[10] = "User defined"
  errMsg[11] = "segmentation violation (ANSI)"
  errMsg[12] = "User defined"
  errMsg[15] = "Termination (ANSI)"
  errMsg[24] = "Soft CPU limit exceeded (4.2 BSD)"
  errMsg[25] = "File size limit exceeded (4.2 BSD)"
  errMsg[29] = "nondefined"
  errMsg[30] = "Power failure restart (System V.)"
  errMsg[33] = "nondefined"
  errMsg[64] = "I/O error: cannot open data file (SEAL)"
  errMsg[65] = "End of job from user application (CMSSW)"
  errMsg[66] = "Application exception"
  errMsg[67] = "unknown"
  errMsg[68] = "unknown"
  errMsg[73] = "Failed writing to read-only file system"
  errMsg[84] = "Some required file not found; check logs for name of missing file."
  errMsg[88] = "unknown"
  errMsg[90] = "Application exception"
  errMsg[100] = "nondefined"
  errMsg[126] = "unknown"
  errMsg[127] = "Error while loading shared library"
  errMsg[129] = "Hangup (POSIX)"
  errMsg[132] = "Illegal instruction (ANSI)"
  errMsg[133] = "Trace trap (POSIX)"
  errMsg[134] = "Abort (ANSI) or IOT trap (4.2 BSD)"
  errMsg[135] = "Bus error (4.2 BSD)"
  errMsg[136] = "unknown"
  errMsg[137] = "killed, unblockable (POSIX) kill -9"
  errMsg[138] = "User defined"
  errMsg[139] = "Segmentation violation (ANSI)"
  errMsg[140] = "User defined"
  errMsg[143] = "Termination (ANSI)"
  errMsg[152] = "CPU limit exceeded (4.2 BSD)"
  errMsg[153] = "File size limit exceeded (4.2 BSD)"
  errMsg[155] = "Profiling alarm clock (4.2 BSD)"
  errMsg[251] = "nondefined"
  errMsg[255] = "nondefined"
  errMsg[256] = "Application exception"
  errMsg[512] = "nondefined"
  errMsg[2304] = "nondefined"
  errMsg[0001] = "Plug-in or message service initialization Exception"

  #cmsRun (CMSSW) exit codes. These codes may depend on specific CMSSW version, the list is maintained in 
  # https://github.com/cms-sw/cmssw/blob/CMSSW_5_0_1/FWCore/Utilities/interface/EDMException.h#L26 and you should
  # look at tags there to find out what is appropriate for a given CMSSW release. The situation as of 5_0_X is below

  # The first three are specific categories of CMS Exceptions.
  errMsg[7000] = "Exception from command line processing"
  errMsg[7001] = "Configuration File Not Found"
  errMsg[7002] = "Configuration File Read Error"
  errMsg[8001] = "Other CMS Exception"
  errMsg[8002] = "std::exception (other than bad_alloc)"
  errMsg[8003] = "Unknown Exception"
  errMsg[8004] = "std::bad_alloc (memory exhaustion)"
  errMsg[8005] = "Bad Exception Type (e.g throwing a string)"

  #The rest are specific categories of CMS Exceptions.
  errMsg[8006] = "ProductNotFound"
  errMsg[8007] = "DictionaryNotFound"
  errMsg[8008] = "InsertFailure"
  errMsg[8009] = "Configuration"
  errMsg[8010] = "LogicError"
  errMsg[8011] = "UnimplementedFeature"
  errMsg[8012] = "InvalidReference"
  errMsg[8013] = "NullPointerError"
  errMsg[8014] = "NoProductSpecified"
  errMsg[8015] = "EventTimeout"
  errMsg[8016] = "EventCorruption"
  errMsg[8017] = "ScheduleExecutionFailure"
  errMsg[8018] = "EventProcessorFailure"
  errMsg[8019] = "FileInPathError"
  errMsg[8020] = "FileOpenError (Likely a site error)"
  errMsg[8021] = "FileReadError (May be a site error)"
  errMsg[8022] = "FatalRootError"
  errMsg[8023] = "MismatchedInputFiles"
  errMsg[8024] = "ProductDoesNotSupportViews"
  errMsg[8025] = "ProductDoesNotSupportPtr"
  errMsg[8026] = "NotFound (something other than a product or dictionary not found)"
  errMsg[8027] = "FormatIncompatibility"
  errMsg[8028] = "FileOpenError with fallback"
           
  #Failures related to the environment setup - range 10000-19999
  errMsg[10001] = "LD_LIBRARY_PATH is not defined"
  errMsg[10002] = "Failed to setup LCG_LD_LIBRAR_PATH"
  errMsg[10016] = "OSG $WORKING_DIR could not be created"
  errMsg[10017] = "OSG $WORKING_DIR could not be deleted"
  errMsg[10018] = "OSG $WORKING_DIR could not be deleted"
  errMsg[10020] = "Shell script cmsset_default.sh to setup cms environment is not found"
  errMsg[10021] = "Failed to scram application project using the afs release area"
  errMsg[10022] = "Failed to scram application project using CMS sw disribution on the LCG2"
  errMsg[10030] = "middleware not identified"
  errMsg[10031] = "Directory VO_CMS_SW_DIR not found"
  errMsg[10032] = "Failed to source CMS Environment setup script such as cmssset_default.sh, grid system or site equivalent script"
  errMsg[10033] = "Platform is incompatible with the scram version"
  errMsg[10034] = "Required application version is not found at the site"
  errMsg[10035] = "Scram Project Command Failed"
  errMsg[10036] = "Scram Runtime Command Failed"
  errMsg[10037] = "Failed to find cms_site_config file in software area"
  errMsg[10038] = "Failed to find cms_site_catalogue.sh file in software area"
  errMsg[10039] = "cms_site_catalogue.sh failed to provide the catalogue"
  errMsg[10040] = "failed to generate cmsRun cfg file at runtime"
  errMsg[10041] = "fail to find valid client for output stage out"
  errMsg[10042] = "Unable to stage-in wrapper tarball."
  errMsg[10043] = "Unable to bootstrap WMCore libraries (most likely site python is broken)."

  #Executable file related failures - range 50000-59999
  errMsg[50110] = "Executable file is not found"
  errMsg[50111] = "Executable file has no exe permissions"
  errMsg[50112] = "User executable shell file is not found"
  errMsg[50113] = "Executable did not get enough arguments"
  errMsg[50114] = "OSG $WORKING_DIR could not be deleted"
  errMsg[50115] = "cmsRun did not produce a valid job report at runtime (often means cmsRun segfaulted)"
  errMsg[50116] = "Could not determine exit code of cmsRun executable at runtime"
  errMsg[50117] = "Could not update exit code in job report (a variation of 50115)"
  errMsg[50513] = "Failure to run SCRAM setup scripts"
  errMsg[50660] = "Application terminated by wrapper because using too much RAM (RSS)"
  errMsg[50661] = "Application terminated by wrapper because using too much Virtual Memory (VSIZE)"
  errMsg[50662] = "Application terminated by wrapper because using too much disk"
  errMsg[50663] = "Application terminated by wrapper because using too much CPU time"
  errMsg[50664] = "Application terminated by wrapper because using too much Wall Clock time"
  errMsg[50669] = "Application terminated by wrapper for not defined reason"
  errMsg[50700] = "Job Wrapper did not produce any usable output file"
  errMsg[50800] = "Application segfaulted (likely user code problem)"
  errMsg[50998] = "Problem calculating file details (i.e. size, checksum etc)"
  errMsg[50999] = "OSG $WORKING_DIR could not be deleted"

  #Staging-OUT related troubles- range 60000-69999
  errMsg[60300] = "Either OutputSE or OutputSE_DIR not defined"
  errMsg[60301] = "Neither zip nor tar exists"
  errMsg[60302] = "Output file(s) not found"
  errMsg[60303] = "File already exists on the SE"
  errMsg[60304] = "Failed to create the summary file (production)"
  errMsg[60305] = "Failed to create a zipped archive (production)"
  errMsg[60306] = "Failed to copy and register output file"
  errMsg[60307] = "Failed to copy an output file to the SE (sometimes caused by timeout issue)."
  errMsg[60308] = "An output file was saved to fall back local SE after failing to copy to remote SE"
  errMsg[60309] = "Failed to create an output directory in the catalogue"
  errMsg[60310] = "Failed to register an output file in the catalogue"
  errMsg[60311] = "Stage Out Failure in ProdAgent job"
  errMsg[60312] = "Failed to get file TURL via lcg-lr command"
  errMsg[60313] = "Failed to delete the output from the previous run via lcg-del command"
  errMsg[60314] = "Failed to invoke ProdAgentStageOut Script"
  errMsg[60315] = "ProdAgent StageOut initialisation error (Due to TFC, SITECONF etc)"
  errMsg[60316] = "Failed to create a directory on the SE"
  errMsg[60317] = "Forced timeout for stuck stage out"
  errMsg[60318] = "Internal error in Crab cmscp.py stageout script"
  errMsg[60319] = "Failure to do asynchronous stageout"
  errMsg[60401] = "Failure to assemble LFN in direct-to-merge by size (WMAgent)"
  errMsg[60402] = "Failure to assemble LFN in direct-to-merge by event (WMAgent)"
  errMsg[60403] = "Timeout during attempted file transfer - status unknown (WMAgent)"
  errMsg[60404] = "Timeout during staging of log archives - status unknown (WMAgent)"
  errMsg[60405] = "General failure to stage out log archives (WMAgent)"
  errMsg[60406] = "Failure in staging in log files during log collection (WMAgent)"
  errMsg[60407] = "Timeout in staging in log files during log collection (WMAgent)"
  errMsg[60408] = "Failure to stage out of log files during log collection (WMAgent)"
  errMsg[60409] = "Timeout in stage out of log files during log collection (WMAgent)"
  errMsg[60410] = "Failure in deleting log files in log collection (WMAgent)"
  errMsg[60411] = "Timeout in deleting log files in log collection (WMAgent)"
  errMsg[60451] = "Output file lacked adler32 checksum (WMAgent)"
  errMsg[60452] = "No run/lumi information in file (WMAgent)"
  errMsg[60453] = "Unable to determine pset hash from output file (CRAB3)"
  errMsg[60999] = "SG $WORKING_DIR could not be deleted"
  errMsg[61101] = "No sites are available to submit the job because the location of its input(s) do not pass the site whitelist/blacklist restrictions (WMAgent)"
  errMsg[61102] = "The job can only run at a site that is currently in Aborted state (WMAgent)"
  errMsg[61103] = "The JobSubmitter component could not load the job pickle (WMAgent)"
  errMsg[61104] = "The job can run only at a site that is currently in Draining state (WMAgent)"
  errMsg[61300] = "The job was killed by the WMAgent, reason is unknown (WMAgent)"
  errMsg[61301] = "The job was killed by the WMAgent because the site it was running at was set to Aborted (WMAgent)"
  errMsg[61302] = "The job was killed by the WMAgent because the site it was running at was set to Draining (WMAgent)"
  errMsg[61303] = "The job was killed by the WMAgent because the site it was running at was set to Down (WMAgent)"

  #Problems saving output via output sandbox- range 70000-70009
  errMsg[70000] = "Output_sandbox too big for WMS: output can not be retrieved"
  errMsg[70500] = "Warning: problem with ModifyJobReport"

  # Other problems
  errMsg[99109] = "Uncaught exception in WMAgent step executor"

  if errorCode in errMsg:
    return errMsg[errorCode]
  else:
    return "ratAutoCrab.py does not know this CRAB error!!!"

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

  task = CRABTask(dirName)

  #getAutoCrabStatus()
  
  vJobs = runCrabStatus(dirName,task,verbose,logCrab)

  while needCrabGet(vJobs):
    runCrabGet(dirName,verbose,logCrab)
    vJobs = runCrabStatus(dirName,task,verbose,logCrab)
    
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






    


