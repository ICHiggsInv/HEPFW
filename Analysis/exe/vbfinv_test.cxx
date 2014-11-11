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
  
  struct timeval tim;

  double t  = 0;
  double t0 = 0;
  double t1 = 0;
  double t2 = 0;
  double t3 = 0;
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  
  gettimeofday(&tim, NULL);
  t0 = tim.tv_sec+(tim.tv_usec/1000000.0);
  
  
  TChain * myTree = new TChain("icEventProducer/EventTree");
  
  for(unsigned i=0; i<vInputFiles.size(); i++){
    myTree->Add(vInputFiles[i].c_str());
  }
  
  gettimeofday(&tim, NULL);
  t1 = tim.tv_sec+(tim.tv_usec/1000000.0);

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
    
    gettimeofday(&tim, NULL);
    double a1 = tim.tv_sec+(tim.tv_usec/1000000.0);
    
    //load the i-th event 
    myTree->LoadTree(i);
    myTree->GetEntry(i);
    
    gettimeofday(&tim, NULL);
    double a2 = tim.tv_sec+(tim.tv_usec/1000000.0);
    
    t += a2-a1;
    
    //process progress
    if(i!=0 && (i%10000)==0){std::cout << "- processing event " << i << "\r" << std::flush;}
    
    hPFMet->Fill(met->pt());
    
    ntot++;
  }
  
  gettimeofday(&tim, NULL);
  t2 = tim.tv_sec+(tim.tv_usec/1000000.0);
  
  gettimeofday(&tim, NULL);
  t3 = tim.tv_sec+(tim.tv_usec/1000000.0);
  
  cout << "Total          time: " << t3-t0 << endl;
  cout << "Total IO Start time: " << t1-t0 << endl;
  cout << "Total IO Ev    time: " << t     << endl;
  cout << "Total IO End   time: " << t3-t2 << endl;  
  
  cout << endl << endl << "Total event processed = " << ntot << endl; 
  
  fOut->Write();
  
  delete myTree;
  
  return 0;
  
};