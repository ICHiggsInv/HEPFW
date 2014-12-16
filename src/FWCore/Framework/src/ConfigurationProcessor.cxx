#include "FWCore/Framework/interface/ConfigurationProcessor.h"


// C++ STD includes
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <algorithm> 

using namespace std;

hepfw::ConfigurationProcessor::ConfigurationProcessor(){

  m_outputFilename = "out.root"; 
  m_maxEvents      = -1;
}

hepfw::ConfigurationProcessor::ConfigurationProcessor(string configFilename){
  
  // Setting variables
  m_maxEvents = -1;
  
  // Determine the absolute location of src directory
  this->getPathSrc();
  
  //
  m_cfgFiles.push_back(configFilename);
  this->loadAllCfg();
  
  
  Json::Value baseFile = this->processFile(configFilename);
  
  const Json::Value filesToLoad = baseFile["load"];
  
  for ( unsigned index = 0; index < filesToLoad.size(); ++index ){
    
    string thisFile = filesToLoad[index].asString();
    //cout << "Files to load " << index << " : " << thisFile << endl;

    if(!(*thisFile.begin()=='/')){
      thisFile=m_pathSrc+thisFile;
    }

    Json::Value          c           = this->processFile(thisFile);
    Json::Value::Members thisMembers = c.getMemberNames();
    for(unsigned i=0; i<thisMembers.size(); i++){
      m_content[ thisMembers[i] ]  = c[ thisMembers[i] ];
    }
  }

  Json::Value::Members baseMembers = baseFile.getMemberNames();
  for(unsigned i=0; i<baseMembers.size(); i++){
    m_content[ baseMembers[i] ]  = baseFile[ baseMembers[i] ];
  }
  
  // Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
  // such member.
  std::string sampleType = m_content["dataset"].get("type","").asString();
  std::string sampleName = m_content["dataset"].get("name","").asString();
  cout << "Dataset type : " << sampleType << endl;
  cout << "Dataset name : " << sampleName << endl;
  
  // Processing input to this jobs
  const Json::Value input = m_content["input"];
  m_maxEvents = input.get("maxEvents",-1).asInt();
  
  const Json::Value fileNames = input["fileNames"];
  for ( unsigned index = 0; index < fileNames.size(); ++index ){
    cout << "inputFiles " << index << " : " << fileNames[index].asString() << endl;
    m_inputFiles.push_back(fileNames[index].asString());
  }

  m_outputFilename = m_content.get("outputFile","out.root").asString();
}

hepfw::ConfigurationProcessor::~ConfigurationProcessor(){

}

std::string hepfw::ConfigurationProcessor::getPathSrc(){
  
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  string path   = string( result, (count > 0) ? count : 0 );

  int countBar=0;
  string::iterator it;
  for(it=path.end()-1; it!=path.begin(); it--){
    if( (*it)=='/'){
      countBar++;
      if(countBar==5){
        it++;
        break;
      }
    }
  }
  
  m_pathSrc = string(path.begin(),it);
  m_pathSrc += "src/";
  
  return m_pathSrc;
  
}

Json::Value hepfw::ConfigurationProcessor::processFile(std::string fileName){
  
  ifstream in(fileName);
  string s((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
  
  Json::Value  root;   // will contains the root value after parsing.
  Json::Reader reader;
  bool parsingSuccessful = reader.parse( s, root );
  if ( !parsingSuccessful ){
    
    cout << "[hepfw::ConfigurationProcessor::processFile] Problems parsing: " << fileName << endl;
    
    // report to the user the failure and their locations in the document.
    cout << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
  }
  
  return root;
}

vector<string> hepfw::ConfigurationProcessor::getInputFiles(){
  return m_inputFiles;
}

Long64_t hepfw::ConfigurationProcessor::getMaxEvents(){
  return m_maxEvents;
}

string hepfw::ConfigurationProcessor::getOutputFile(){
  return m_outputFilename;
}

vector<string> hepfw::ConfigurationProcessor::getRunSequences(){

  vector<string> out;

  const Json::Value runSeqNames = m_content["runSequences"];
  for ( unsigned index = 0; index < runSeqNames.size(); ++index ){
    out.push_back(runSeqNames[index].asString());
  }
  
  return out;
}

vector<string> hepfw::ConfigurationProcessor::getSequenceModules(string sequenceName){
  
  vector<string> out;
  
  // Attempting to get module with
  const Json::Value module = m_content[sequenceName];
  
  if(!module.get("sequence",false).asBool()){
    cout << "[hepfw::ConfigurationProcessor::getSequenceModules] ERROR: Attempt to get modules for non-sequence type object \"" << sequenceName << "\"" << endl;
    return out;
  }
  
  const Json::Value moduleNames = module["modules"];
  for ( unsigned index = 0; index < moduleNames.size(); ++index ){
    out.push_back(moduleNames[index].asString());
  }
  
  return out;
  
}

hepfw::ParameterSet hepfw::ConfigurationProcessor::getModuleParameters(std::string moduleName){
  
  const Json::Value module = m_content[moduleName];

  hepfw::ParameterSet pset(module["parameters"]);

  return pset;
  
}

string hepfw::ConfigurationProcessor::getModuleClass(std::string moduleName){
  
  const Json::Value module = m_content[moduleName];
  
  return module.get("module","").asString();
  
}

void hepfw::ConfigurationProcessor::loadAllCfg(){
  
  vector<Json::Value> content;
  
  for(unsigned i=0; i<m_cfgFiles.size(); i++){
    
    string *filePath = &m_cfgFiles[i];
    
    Json::Value fileContent = this->processFile(*filePath);
    content.push_back(fileContent);
    
    Json::Value filesToLoad = fileContent["load"];
    
    for ( unsigned index = 0; index < filesToLoad.size(); ++index ){
      
      string thisFile = filesToLoad[index].asString();
      
      // if its a relative path convert to absolute (assume base is src directory)
      if(!(*thisFile.begin()=='/')){thisFile=m_pathSrc+thisFile;}
      
      // If the file to load is already on the list continue
      vector<string>::iterator it = find (m_cfgFiles.begin(),m_cfgFiles.end(),thisFile);
      if (it != m_cfgFiles.end()){continue;}
      
      cout << "Files to load " << index << " : " << thisFile << endl;
      m_cfgFiles.push_back(thisFile);
      
    }
  }
  
  for(int i=content.size()-1; i>=0; i--){
    
    Json::Value          *var         = &content[unsigned(i)];
    Json::Value::Members  fileMembers = var->getMemberNames();

    for(unsigned a=0; a<fileMembers.size(); a++){
      m_content[ fileMembers[a] ]  = (*var)[ fileMembers[a] ];
    }
  }
}
