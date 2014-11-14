#include "FWCore/Framework/interface/ConfigurationProcessor.h"

// HEPFW includes
#include "Parameters/JSONParser/interface/json.h"

// C++ STD includes
#include <iostream>
#include <fstream>

using namespace std;

hepfw::ConfigurationProcessor::ConfigurationProcessor(){

  m_outputFilename = "out.root"; 

}

hepfw::ConfigurationProcessor::ConfigurationProcessor(string configFilename){

  ifstream in(configFilename);
  string s((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
  
  Json::Value  root;   // will contains the root value after parsing.
  Json::Reader reader;
  bool parsingSuccessful = reader.parse( s, root );
  if ( !parsingSuccessful ){
    
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
    << reader.getFormattedErrorMessages();
    //return 1;
  }
  
  // Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
  // such member.
  std::string sampleType = root["sample"].get("type","").asString();
  std::string sampleName = root["sample"].get("name","").asString();
  cout << "Sample type : " << sampleType << endl;
  cout << "Sample name : " << sampleName << endl;
  
  const Json::Value plugins = root["inputFiles"];
  for ( unsigned index = 0; index < plugins.size(); ++index ){
    cout << "inputFiles " << index << " : " << plugins[index].asString() << endl;
    m_inputFiles.push_back(plugins[index].asString());
  }
  
  m_outputFilename = root.get("outputFile","out.root").asString();
}

hepfw::ConfigurationProcessor::~ConfigurationProcessor(){

}

vector<string> hepfw::ConfigurationProcessor::getInputFiles(){
  return m_inputFiles;
}

string hepfw::ConfigurationProcessor::getOutputFile(){
  return m_outputFilename;
}