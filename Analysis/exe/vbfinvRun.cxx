// HEPFW includes
#include "FWCore/Framework/interface/ConfigurationProcessor.h"
#include "FWCore/Framework/interface/EventProcessor.h"
#include "FWCore/IO/interface/File.h"
#include "Plots/Style/interface/Style.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

// ROOT includes
#include "TFile.h"
#include "TH1I.h"
#include "TH1D.h"

// C++ STD includes
#include <string>
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
  
  bool incorrectCmd = false;
  char *cfgFile;
  if(argc!=2){incorrectCmd=true;}
  
  if(incorrectCmd){
    printf("Usage: %s [cfgFile]\n", argv[0]);
    return 1;
  }
  else{cfgFile = argv[1];}
  
  hepfw::ConfigurationProcessor myCfgProcessor(argv[1]);
  string outputFilename = myCfgProcessor.getOutputFile();

  hepfw::EventProcessor myEventProcessor(&myCfgProcessor);
  Long64_t nevents = myEventProcessor.getNEvent();
  cout << "Number of entries: " << nevents << endl;
  
  hepfw::File fOut(outputFilename.c_str(),"RECREATE");
  
  TH1I hEventCount("EventCount","EventCount",1,0.5,1.5); hEventCount.SetDirectory(&fOut);
//   TH1D hPFMet     ("PFMet","PFMet",1000,0,1000);         hPFMet     .SetDirectory(&fOut);
  TH1D hPFMet2    ("PFMet2","PFMet2",1000,0,1000);       hPFMet2    .SetDirectory(&fOut);
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  int ntot=0;
  
  //loop over the events
  for (Long64_t i=0; i<nevents; i++){
    
    hEventCount.Fill(1);
    
    hepfw::Event* ev = myEventProcessor.getEvent(i);
    
    //process progress
    if(i!=0 && (i%10000)==0){std::cout << "- processing event " << i << "\r" << std::flush;}
    
//     hPFMet .Fill(ev->getPFMet()->pt());
    ic::Met* met = ev->getByName<ic::Met>("pfMet");
    hPFMet2.Fill(met->pt());
    
    delete ev;
    ntot++;
    
  }
  
  cout << endl << endl << "Total event processed = " << ntot << endl; 
  
  fOut.Write();
  fOut.Close();

  return 0;
  
};