// HEPFW includes
#include "Parameters/JSONParser/interface/json.h"
#include "FWCore/IO/interface/File.h"
#include "Plots/Style/interface/Style.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

// ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1D.h"

// C++ STD includes
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>
#include <ctime>

using namespace std;

//#################################################################################
//#################################################################################
//#################################################################################
int main(int argc, char *argv[]){
  
  bool incorrectCmd = false;
  char *cfgFile;
  if(argc!=2){incorrectCmd=true;}
  
  if(incorrectCmd){
    printf("Usage: %s [cfgFile]\n", argv[0]);
    return 1;
  }
  else{cfgFile = argv[1];}
  
  std::ifstream in(cfgFile);
  std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  
  Json::Value  root;   // will contains the root value after parsing.
  Json::Reader reader;
  bool parsingSuccessful = reader.parse( s, root );
  if ( !parsingSuccessful )
  {
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
    << reader.getFormattedErrorMessages();
    return 1;
  }
  
  // Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
  // such member.
  std::string sampleType = root["sample"].get("type","").asString();
  std::string sampleName = root["sample"].get("name","").asString();
  cout << "Sample type : " << sampleType << endl;
  cout << "Sample name : " << sampleName << endl;

  vector<string> vInputFiles;
  
  // Get the value of the member of root named 'encoding', return a 'null' value if
  // there is no such member.
  const Json::Value plugins = root["inputFiles"];
  for ( unsigned index = 0; index < plugins.size(); ++index ){
    cout << "inputFiles " << index << " : " << plugins[index].asString() << endl;
    vInputFiles.push_back(plugins[index].asString());
  }

  string outputFilename = root.get("outputFile", "out.root" ).asString();
  hepfw::File *fOut = new hepfw::File(outputFilename.c_str(),"RECREATE");
  
  TH1I* hEventCount = new TH1I("EventCount","EventCount",1,0.5,1.5); hEventCount->SetDirectory(fOut);
  TH1D* hPFMet      = new TH1D("PFMet","PFMet",1000,0,1000);         hPFMet     ->SetDirectory(fOut);
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  
  TChain * myTree = new TChain("icEventProducer/EventTree");
  
  for(unsigned i=0; i<vInputFiles.size(); i++){
    myTree->Add(vInputFiles[i].c_str());
  }

  Long64_t nentries = myTree->GetEntries();
  Long64_t nevents  = nentries;
  cout << "Number of entries: " << nentries << endl;
  
  vector<ic::GenParticle> *gen = new vector<ic::GenParticle>();
  ic::Met                 *met = new ic::Met();
  myTree->SetBranchAddress("genParticles",&gen);
  myTree->SetBranchAddress("pfMet",       &met);
  
  int ntot=0;
  
  //loop over the events
  for (Long64_t i=0; i<nevents; i++){
    
    hEventCount->Fill(1);
    
    //load the i-th event 
    myTree->LoadTree(i);
    myTree->GetEntry(i);
    
    
    //process progress
    if(i!=0 && (i%10000)==0){std::cout << "- processing event " << i << "\r" << std::flush;}
    
    hPFMet->Fill(met->pt());
    
    ntot++;
  }
  
  cout << endl << endl << "Total event processed = " << ntot << endl; 
  
  fOut->Write();
  
  delete myTree;
  
  return 0;
  
};