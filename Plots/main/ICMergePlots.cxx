// TODO: Description

// ICTools includes
#include "ICTools/Parameters/interface/ICParameterSet.h"
#include "ICTools/Parameters/interface/ICParameterParser.h"

// ROOT includes
#include "TFile.h"

// Standard libraries includes
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

  // Caching command line parameters  
  bool hasCfg = false; string cfgFile = "";

  int firstArg=1;
  
  if(argc<3){
    printf("Usage: %s [options] <OutputFile> <InputFile0> (...)\n", argv[0]);
    printf("Possible options:\n");
    printf("-cfg <file>  : input configuration file\n");
    
    return 0;
  }
  
  for(int i=1; i<argc; i=i+2){
    if(!strcmp(argv[i],"-cfg")){
      hasCfg    = true;
      cfgFile   = argv[i+1];
      firstArg += i+2;
      printf("Using cfg file: %s\n",cfgFile.c_str());      
    }
    else{break;}
  }
  
  if(hasCfg){
    cout<<"Processing parameters..."<<endl;
    ICParameterParser myPar(cfgFile);
    cout << "Number of PSet        : " << myPar.getNPSet() << endl;
    cout << "Is PSet:Global Defined: " << myPar.isPSetSet("Global") << endl;
    if(myPar.isPSetSet("Global")){
      cout<<myPar.getByName("Global").toString()<<endl;
    }
  }
  
  printf("Output file: %s\n", argv[firstArg]);
  
  map<string,TFile*> inputFiles;
  for(int i=firstArg+1; i<argc; i++){
    printf("Input file: %s\n", argv[i]);
  }
  
  return 0;
}

