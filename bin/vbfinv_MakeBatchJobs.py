#!/usr/bin/python

import os
import stat
import sys
from optparse import OptionParser
import FWCore.ParameterSet.Config as cms

def find_between( s, first, last ):
  try:
    start = s.index( first ) + len( first )
    end   = s.index( last, start )
    return s[start:end]
  except ValueError:
    return ""

parser = OptionParser()
parser.add_option('--fileList',    dest="fileList",help='')
parser.add_option('--filePrefix',  dest="filePrefix",help='')
parser.add_option('--sampleType',  dest="sampleType",help='')
parser.add_option('--sampleGroup', dest="sampleGroup",help='')
parser.add_option('--sampleName',  dest="sampleName",help='')
parser.add_option('--numberOfJobs',dest="numberOfJobs",help='')
parser.add_option('--outputFolder',dest="outputFolder",help='')
(options, args) = parser.parse_args()

outputFolder = '';

if options.fileList is None:
  parser.error('fileList not given')
if options.filePrefix is None:
  parser.error('filePrefix not given')
if options.sampleType is None:
  parser.error('sampleType not given')
if options.sampleGroup is None:
  parser.error('sampleGroup not given')
if options.sampleName is None:
  parser.error('sampleName not given')
if options.numberOfJobs is None:
  parser.error('numberOfJobs not given')
if options.outputFolder is not None:
  outputFolder=options.outputFolder+"/"
  if not os.path.exists(outputFolder):
    os.makedirs(outputFolder)


nJobs = int(options.numberOfJobs)
inputFiles = list()

with open(options.fileList, 'r') as f:
  for line in f:
    if line.find('.root') != -1:
      inputFiles.append(options.filePrefix+line.rstrip())
    
#print "Found "+str(len(inputFiles))+" input files."

nInputFiles = len(inputFiles)

if nInputFiles<nJobs:
  print "Number of jobs is bigger than number of input files... exiting"
  sys.exit()

filesPerJob = float(nInputFiles) / float(nJobs)
print "Making Jobs "+options.numberOfJobs+" ("+str(filesPerJob)+" files per job) for type="+options.sampleType+" group="+options.sampleGroup+" name="+options.sampleName+" with filelist="+options.fileList

fSubmit = open(outputFolder+'submitJobs.sh','w')
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

  with open(outputFolder+'job'+str(x)+'_cfg.json','w') as fOut:
    
    fOut.write("{\n");
    fOut.write("\n");
    fOut.write("  \"load\" : [\"VBFHiggsToInvisible/Analysis/data/sampleData.json\"],\n");
    fOut.write("  \"load\" : [\"VBFHiggsToInvisible/Analysis/data/sequence_SignalSelection.json\"],\n");
    fOut.write("\n");
    fOut.write("  \"job\"  : {\n");
    fOut.write("    \"verbose\" : \"false\"\n");
    fOut.write("  }, \n");
    fOut.write("\n");
    fOut.write("  \"dataset\" : {\n"); 
    fOut.write("    \"type\"  : \""+options.sampleType+"\",\n");
    fOut.write("    \"group\" : \""+options.sampleGroup+"\",\n");
    fOut.write("    \"name\"  : \""+options.sampleName+"\"\n");
    fOut.write("  },\n");
    fOut.write("\n");
    fOut.write("  \"runSequences\" : [\"signalRegion\"],\n");
    fOut.write("\n");
    fOut.write("  \"input\" : {\n");
    fOut.write("    \"maxEvents\" : -1,\n");
    fOut.write("    \"fileNames\" : [\n");
    for idx,val in enumerate(jobInputFiles):
      fOut.write("      \""+val+"\"");
      if idx<len(jobInputFiles)-1:
        fOut.write(",");
      fOut.write("\n");
    fOut.write("    ]\n");
    fOut.write("  },\n");
    fOut.write("\n");
    fOut.write("  \"outputFile\" : \"results_Job"+str(x)+".root\"\n");
    fOut.write("\n");
    fOut.write("}\n");
    fOut.write("\n");

  with open(outputFolder+'runJob'+str(x)+'.sh','w') as fOut:
    fOut.write("#!/bin/bash\n")
    fOut.write("\n")
    fOut.write("cd /vols/cms02/jca10/work/slc6/dev01/CMSSW_5_3_11/src\n");
    fOut.write("eval `scramv1 runtime -sh`\n");
    fOut.write("cd /vols/cms02/jca10/work/slc6/dev01/HEPFW/bin\n");
    fOut.write("source thisHEPFW.sh\n");
    fOut.write("cd "+os.getcwd()+"/"+outputFolder+"\n")
    fOut.write("vbfinvRun job"+str(x)+"_cfg.json\n")

  os.chmod(outputFolder+'runJob'+str(x)+'.sh', stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)

  os.chmod(outputFolder+'submitJobs.sh', stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
