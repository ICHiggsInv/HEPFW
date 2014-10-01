// TODO: Description

// RATools includes
#include "Parameters/Parser/interface/ParameterSet.h"
#include "Parameters/Parser/interface/ParameterParser.h"

// ROOT includes
#include "TFile.h"

// Standard libraries includes
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string,double> calcSampleWeights (hepfw::ParameterSet global,vector<string> samples,hepfw::ParameterSet xsecs,hepfw::ParameterSet events){
  
  map<string,double> out;

  // Retrive values from PSet
  double dataLumi = global.getDouble("reweightLumi");

  cout <<"Data Luminosity: "<<dataLumi<<" pb-1"<<endl;
  
  for(unsigned s=0; s<samples.size(); s++){
  
    string sampleName = samples[s]; 

    // Checking if the necessary variables are defined for this sample
    if(!xsecs .isSetDouble(sampleName)){continue;}
    if(!events.isSetInt   (sampleName)){continue;}
    
    double weight = (dataLumi * xsecs.getDouble(sampleName)) / events.getInt(sampleName);
    
    cout << "sample: "<< sampleName << " weight:" << weight << endl;
    
    out[sampleName] = weight;
  }
  
  return out;
}

int main(int argc, char *argv[]){

  // Caching command line parameters  
  bool hasCfg   = false; string cfgFile = "";
  int  firstArg = 1;
  
  if(argc<3){
    printf("Usage: %s [options] <OutputFile> <InputFile0> (...)\n", argv[0]);
    printf("Possible options:\n");
    printf("-cfg <file>  : input configuration file\n");
    
    return 0;
  }
  
  for(int i=1; i<argc; i=i+2){
    if(!strcmp(argv[i],"-cfg")){
      hasCfg   = true;
      cfgFile  = argv[i+1];
      firstArg = i+2;
      printf("Using cfg file: %s\n",cfgFile.c_str());      
    }
    else{break;}
  }

  // Now lets read the files
  TFile              *fOut;
  map<string,TFile*>  fIn;
  vector<string>      sampleNames;
  
  printf("Output file: %s\n", argv[firstArg]);
  fOut = new TFile(argv[firstArg],"RECREATE");
  
  map<string,TFile*> inputFiles;
  for(int i=firstArg+1; i<argc; i++){
    
    // Output the filenames 
    printf("Input file: %s\n", argv[i]);

    string sArg(argv[i]);
    
    // Removing extension
    int    indexDot   = sArg.find_last_of("."); 
    string sampleName = sArg.substr(0, indexDot);
    
    sampleNames.push_back(sampleName);
    
    fIn[sampleName] = new TFile(argv[i],"RECREATE");
  }
  
  map<string,double> sampleWeights;
  
  if(hasCfg){
    cout<<"Processing parameters..."<<endl;
    hepfw::ParameterParser myPar(cfgFile);
    cout << "Number of PSet         : " << myPar.getNPSet() << endl;
    cout << "Is PSet:Global  Defined: " << myPar.isPSetSet("Global") << endl;
    cout << "Is PSet:XSecs   Defined: " << myPar.isPSetSet("XSecs") << endl;
    cout << "Is PSet:Events  Defined: " << myPar.isPSetSet("Events") << endl;
    cout << "Is PSet:Merge   Defined: " << myPar.isPSetSet("Merge") << endl;
    
    hepfw::ParameterSet pSetGlobal,pSetEvents,pSetMerge;
    if(myPar.isPSetSet("Global")){pSetGlobal  = myPar.getByName("Global");}
    if(myPar.isPSetSet("Merge")) {pSetMerge   = myPar.getByName("Merge");}
    
    if(pSetGlobal.getBool("doReweight")){
      
      cout << "Calculating weights..." << endl;
      
      hepfw::ParameterSet pSetXSecs,pSetEvents;
      if(myPar.isPSetSet("XSecs")){pSetXSecs = myPar.getByName("XSecs");}
      else{return 0;}
      if(myPar.isPSetSet("Events")) {pSetEvents  = myPar.getByName("Events");}
      else{return 0;}
      
      sampleWeights = calcSampleWeights(pSetGlobal,sampleNames,pSetXSecs,pSetEvents);
      
    }
    
  }
  
  return 0;
}
