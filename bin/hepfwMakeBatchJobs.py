#!/usr/bin/python

import os
import stat
import sys
import json
from optparse import OptionParser

def find_between( s, first, last ):
  try:
    start = s.index( first ) + len( first )
    end   = s.index( last, start )
    return s[start:end]
  except ValueError:
    return ""

def makeJobCfg(path,inFiles,outFile):
  
  with open(path,'w') as fOut:
    with open(options.fileCfg) as contentCfg:
      
      fileContent = contentCfg.read();
      content     = json.loads(fileContent);
      
      # Setting input file list
      content["input"]["fileNames"] = inFiles;
      content["input"]["maxEvents"] = -1;
      
      # Setting output file name
      content["outputFile"] = outFile;
      
      # Setting dataset options
      content["dataset"]["type"]  = options.sampleType
      content["dataset"]["group"] = options.sampleGroup
      content["dataset"]["name"]  = options.sampleName
      
      fOut.write(json.dumps(content,sort_keys=True,indent=2,separators=(',', ' : ')))
      fOut.close()
      
      # Debug
      #print json.dumps(content,sort_keys=True,indent=2,separators=(',', ': '))

def makeJobCfg_2(path,index):
  
  with open(path,'w') as fOut:
    fOut.write("{\n");
    fOut.write("\n");
    fOut.write("  \"load\" : [\"VBFHiggsToInvisible/Analysis/data/sampleData.json\"],\n");
    fOut.write("  \"load\" : [\"VBFHiggsToInvisible/Analysis/data/sequence_SignalSelection.json\"],\n");
    fOut.write("  \"load\" : [\"VBFHiggsToInvisible/Analysis/data/sequence_QCDSelection.json\"],\n");
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
    fOut.write("  \"runSequences\" : [\"qcdRegion\"],\n");
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

def makeJobExe(path,index):
  
  with open(path,'w') as fOut:
    fOut.write("#!/bin/bash\n")
    fOut.write("\n")
    fOut.write("cd /vols/cms02/jca10/work/slc6/dev01/cc/CMSSW_5_3_32/src\n");
    fOut.write("eval `scramv1 runtime -sh`\n");
    fOut.write("cd /vols/cms02/jca10/work/slc6/dev01/cc/HEPFW_v2/bin\n");
    fOut.write("source thisHEPFW.sh\n");
    fOut.write("cd "+os.getcwd()+"/"+outputFolder+"\n")
    fOut.write("vbfinvRun job"+str(index)+"_cfg.json\n")

  os.chmod(outputFolder+'runJob'+str(index)+'.sh', stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)







parser = OptionParser()
parser.add_option('--fileList',    dest="fileList",    help='')
parser.add_option('--filePrefix',  dest="filePrefix",  help='')
parser.add_option('--fileCfg',     dest="fileCfg",     help='')
parser.add_option('--sampleType',  dest="sampleType",  help='')
parser.add_option('--sampleGroup', dest="sampleGroup", help='')
parser.add_option('--sampleName',  dest="sampleName",  help='')
parser.add_option('--numberOfJobs',dest="numberOfJobs",help='')
parser.add_option('--outputFolder',dest="outputFolder",help='')
(options, args) = parser.parse_args()

outputFolder = '';

if options.fileList is None:
  parser.error('fileList not given')
if options.filePrefix is None:
  parser.error('filePrefix not given')
if options.fileCfg is None:
  parser.error('fileCfg not given')
if options.sampleType is None:
  parser.error('sampleType not given')
if options.sampleGroup is None:
  parser.error('sampleGroup not given')
if options.sampleName is None:
  parser.error('sampleName not given')
if options.numberOfJobs is None:
  parser.error('numberOfJobs not given')


# If the output folder does not exist create it
if options.outputFolder is not None:
  outputFolder=options.outputFolder+"/"
  if not os.path.exists(outputFolder):
    os.makedirs(outputFolder)


# Now beginning processing
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

  makeJobCfg(outputFolder+'job'+str(x)+'_cfg.json',jobInputFiles,"results_Job"+str(x)+".root");
  makeJobExe(outputFolder+'runJob'+str(x)+'.sh',x);


  os.chmod(outputFolder+'submitJobs.sh', stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)





