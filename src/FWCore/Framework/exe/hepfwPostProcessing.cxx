// HEPFW includes
#include "FWCore/IO/interface/File.h"
#include "FWCore/ErrorManagement/interface/ErrorManagement.h"
#include "Plots/Style/interface/Style.h"

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
  
  // Error management
  hepfw::ErrorManagement errorManager;
  
  // Parameters;
  string filename_cfg = "";

  for(int i=1; i<argc; i++){
    
    if(strcmp(argv[i],"-c") || strcmp(argv[i],"--cfg")){
      if(i+1>=argc){
        errorManager.addError("hepfwPostProcessing",hepfw::ErrorManagement::ErrorType::ErrorFatal,Form("Option %s called but no argument supplied\n",argv[i]));
        break;
      }else{
        filename_cfg = argv[i+1];
      }
    }
  }
  
  // Checking for variables 
  if(filename_cfg==""){
    errorManager.addError("hepfwPostProcessing",hepfw::ErrorManagement::ErrorType::ErrorFatal,"No configuration file provided. Please supply one using -c or --cfg.\n");
  }
  
  // Stopping job here it there are errors
  if(errorManager.getJobStop()){return errorManager.getJobEnd();}
  
  //
  hepfw::Style myStyle;
  myStyle.setTDRStyle();

  return errorManager.getJobEnd();
  
};

