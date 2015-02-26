// HEPFW includes
#include "FWCore/IO/interface/File.h"
#include "FWCore/ErrorManagement/interface/ErrorManagement.h"
#include "FWCore/Framework/interface/ConfigurationProcessor.h"
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "PostProcessing/Data/interface/ProcessedDataManager.h"
#include "Plots/Style/interface/Style.h"


// HEPFW special includes 
#include "FWCore/Framework/scan/PostProcessingModulesScan.h"

// ROOT included
#include "TString.h"

// C++ STD includes
#include <string>
#include <cstring>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <ctime>

using namespace std;

//#################################################################################
//#################################################################################
//#################################################################################
int main(int argc, char *argv[]){
  
  // Starting managers
  hepfw::ErrorManagement      errorManager; // Error management

  
  // Parameters;
  string filename_cfg = "";

  for(int i=1; i<argc; i++){
    
    if(strcmp(argv[i],"-c") || strcmp(argv[i],"--cfg")){
      if(i+1>=argc){
        errorManager.addError(
          "hepfwPostProcessing",
          hepfw::ErrorManagement::ErrorType::ErrorFatal,
          Form("Option %s called but no argument supplied\n",argv[i])
        );
        break;
      }else{filename_cfg = argv[i+1]; i++;}
    }
  }
  
  // Checking for variables 
  if(filename_cfg==""){
    errorManager.addError(
      "hepfwPostProcessing",
      hepfw::ErrorManagement::ErrorType::ErrorFatal,
      "No configuration file provided. Please supply one using -c or --cfg.\n"
    );
  }
  
  if(errorManager.getJobStop()){return errorManager.getJobEnd();} // Stopping job here it there are errors

  hepfw::ConfigurationProcessor cfgProcessor(filename_cfg,"PostProcessing");
  cfgProcessor.setErrorManager(&errorManager);

  hepfw::ParameterSet psJob = cfgProcessor.get("job");
  std::vector<string> vSeq  = psJob.getParameterVector<std::string>("runSequences");
  
  if(psJob.getParameter<bool>("verbose")){cout << "Verbose: True" << endl;}
  else                                   {cout << "Verbose: False" << endl;}

  cout << "We are going to run Sequences:" << endl;

  map<std::string,hepfw::PostProcessingModule*> myModules; 

  for(unsigned i=0; i<vSeq.size(); i++){
    cout << "=> Sequence: " << vSeq[i] << endl;

    hepfw::ParameterSet iSeq = cfgProcessor.get(vSeq[i]);
    std::vector<string> vMod = iSeq.getParameterVector<std::string>("modules");
      
    cout << "With Modules:" << endl;
    for(unsigned a=0; a<vMod.size(); a++){

      cout << "==> Module: " << vMod[i] << endl;
      
      map<std::string,hepfw::PostProcessingModule*>::iterator it = myModules.find(vMod[i]);
      if(it == myModules.end()){
	
        hepfw::ParameterSet pMod = cfgProcessor.get(vMod[i]);
	
	string              moduleClass = pMod.getParameter<std::string>("module");
        hepfw::ParameterSet modulePSet  = pMod.getParameterSet("parameters");

	hepfw::PostProcessingModule* thisModule = hepfw::hepfwGetPostProcessingModule(moduleClass,vMod[i],modulePSet);
	myModules[ vMod[i] ] = thisModule;
      }
    }    
  }

  if(errorManager.getJobStop()){return errorManager.getJobEnd();} // Stopping job here it there are errors

  // Starting the ProcessedDataManager to deal with the input data
  hepfw::ParameterSet psData = cfgProcessor.get("Data");
  hepfw::ProcessedDataManager dataManager(psData);
  
  // Setting style for plots
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  for(auto i=myModules.begin(); i!=myModules.end(); i++){
    i->second->process(dataManager);
  }
  
  return errorManager.getJobEnd();
  
};

