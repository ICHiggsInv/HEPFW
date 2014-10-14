#!/usr/bin/python

import os
import stat
import sys
import argparse
import FWCore.ParameterSet.Config as cms

def find_between( s, first, last ):
  try:
    start = s.index( first ) + len( first )
    end   = s.index( last, start )
    return s[start:end]
  except ValueError:
    return ""


parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('--inputFileList',  help='',required=True)
parser.add_argument('--inputConfigFile',help='',required=True)
parser.add_argument('--numberOfJobs',   help='',required=True)

args = vars(parser.parse_args())
print args['inputFileList']
print args['inputConfigFile']
print args['numberOfJobs']

nJobs = int(args['numberOfJobs'])
inputFiles = list()

with open(args['inputFileList'], 'r') as f:
  for line in f:
    pos = find_between(line,str("\'"),str("\'"))
    if len(pos)>0:
      inputFiles.append(pos)
      
    
print "Found "+str(len(inputFiles))+" input files."

nInputFiles = len(inputFiles)

if nInputFiles<nJobs:
  print "Number of jobs is bigger than number of input files... exiting"
  sys.exit()

filesPerJob = float(nInputFiles) / float(nJobs)
print "Files per job "+str(filesPerJob)

fSubmit = open('submitJobs.sh','w')
fSubmit.write("#!/bin/sh\n")
fSubmit.write("\n")
  
fileIndex = 0
for x in range(0,nJobs):
  #print "We're on job %d" % (x)
  
  fSubmit.write("qsub -q hepshort.q runJob"+str(x)+".sh\n")
  
  jobInputFiles = list()
  
  while fileIndex < (x+1)*filesPerJob:
    jobInputFiles.append(inputFiles[fileIndex])
    #print "File #"+str(fileIndex)+" - "+inputFiles[fileIndex]
    fileIndex=fileIndex+1

  #print "=> Number of input files: "+str(len(jobInputFiles))

  with open('job'+str(x)+'_cfg.py','w') as fOut:
    with open(args['inputConfigFile'], 'r') as fIn:
      for line in fIn:
        
        pos = line.find('process = cms.Process')
        if pos != -1:
          fOut.write(line)
          fOut.write("\n")
          fOut.write("process.source = cms.Source(\"PoolSource\",\n")
          fOut.write("  fileNames = cms.untracked.vstring(\n")
          for f in jobInputFiles:
            fOut.write("    '"+f+"',\n")
          fOut.write("  ),\n")
          fOut.write(")\n")
          fOut.write("process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )\n")
          continue
        
        pos = line.find('outputFilename')
        if pos != -1:
          newLine = line.replace(str(".root"),str('_job'+str(x)+'.root'))
          fOut.write(newLine)
        else:
          fOut.write(line)
  
  with open('runJob'+str(x)+'.sh','w') as fOut:
    fOut.write("#!/bin/sh\n")
    fOut.write("\n")
    fOut.write("source /vols/cms/grid/setup.sh\n")
    fOut.write("cd "+os.getcwd()+"\n")
    fOut.write("eval `scramv1 runtime -sh`\n")
    fOut.write("cmsRun job"+str(x)+"_cfg.py\n")

  os.chmod('runJob'+str(x)+'.sh', stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)

  os.chmod('submitJobs.sh', stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
