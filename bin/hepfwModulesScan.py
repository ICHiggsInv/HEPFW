#!/usr/bin/python

import os
import fnmatch
import sys

def find_between( s, first, last ):
    try:
        start = s.index( first ) + len( first )
        end = s.index( last, start )
        return s[start:end]
    except ValueError:
        return ""

def find_between_r( s, first, last ):
    try:
        start = s.rindex( first ) + len( first )
        end = s.rindex( last, start )
        return s[start:end]
    except ValueError:
        return ""


print os.environ['HEPFWSYS']

pathSrc = os.environ['HEPFWSYS']+'/src/'

outFile = open(pathSrc+"FWCore/Framework/interface/ModulesScan.h", 'w')

outFile.write("// This file is generated automatically by the script hepfwModuleScan.py\n");
outFile.write("// DO NOT change any of the contents below\n");
outFile.write("\n");

matches = []
for root, dirnames, filenames in os.walk(pathSrc):
  for filename in fnmatch.filter(filenames, '*.h'):
    matches.append(os.path.join(root, filename))
    

modules = []
for m in matches:
  with open(m,'r') as f:
    for line in f:
      if line.find('//DECLARE_HEPFW_MODULE') != -1:
        outFile.write("#include \""+m.replace(pathSrc,"")+"\"\n");
        modules.append(line)

outFile.write("\n");
outFile.write("#include \"FWCore/Parameters/interface/ParameterSet.h\"\n");
outFile.write("#include \"FWCore/Modules/interface/Module.h\"\n");
outFile.write("\n");
outFile.write("#include <string>\n");
outFile.write("\n");
outFile.write("using namespace std;\n");
outFile.write("\n");
outFile.write("namespace hepfw{\n");
outFile.write("\n");
outFile.write("  hepfw::Module* hepfwGetModule(std::string className, std::string instanceName, hepfw::ParameterSet &pset){\n");
outFile.write("\n");
outFile.write("    hepfw::Module *out = 0;\n");
outFile.write("    if(className==\"\"){\n");
outFile.write("      cout << \"[hepfw::hepfwGetModule] Warning: Initialising default class since provided class name was null...\" << endl;\n");
outFile.write("      out = new hepfw::Module(instanceName,pset);\n");
outFile.write("    }\n");

for m in modules:
  name = find_between(m,'(',')')
  outFile.write("    else if(className==\""+name+"\"){out = new "+name+"(instanceName,pset);}\n");
  print "Registering module :",name
  
outFile.write("    else{\n");
outFile.write("      out = new hepfw::Module(instanceName,pset);\n");
outFile.write("      cout << \"[hepfw::hepfwGetModule] Warning: Initialising default class since provided class is not know (name=\"<<className<<\")\" << endl;\n");
outFile.write("    }\n");
outFile.write("\n");
outFile.write("    return out;\n");
outFile.write("\n");
outFile.write("  }\n");
outFile.write("}\n");
outFile.close()
