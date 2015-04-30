// TODO: Description

// ICTools includes
#include "Histograms/Analysis/interface/HistogramCollection.h"

#include "TH1D.h"
#include "TCanvas.h"

// Standard libraries includes
#include <iostream>
#include <string>


using namespace std;

int main(int argc, char *argv[]){
  
  TH1D* h0 = new TH1D("h0","h0",100,0,1);
  TH1D* h1 = new TH1D("h1","h1",100,0,1);
  TH1D* h2 = new TH1D("h2","h2",100,0,1);
  
  h0->FillRandom("gaus", 50000);
  h1->FillRandom("landau",50000);
  h2->FillRandom("expo",  50000);  

  hepfw::HistogramCollection<string,TH1D> hCol;  
  hCol.insert(pair<string,TH1D*>("h0",h0));
  hCol.insert(pair<string,TH1D*>("h1",h1));
  hCol.insert(pair<string,TH1D*>("h2",h2));
  
  TCanvas c("Example Histogram Collection");
  vector< pair<string,Option_t*> > options;
  options.push_back(pair<string,Option_t*>("h0",""));
  options.push_back(pair<string,Option_t*>("h1","same"));
  options.push_back(pair<string,Option_t*>("h2","same"));
  
  map<string,int> lineColor;  
  lineColor["h0"] = kRed;
  lineColor["h1"] = kBlue;
  lineColor["h2"] = kGreen;
  
  hCol.setLineColor(lineColor);
  hCol.scaleTo1();
  hCol.draw(&c,options);
  
  c.SaveAs("ExampleHistogramCollection.png");
  
  
  delete h0;
  delete h1;
  delete h2;
  
  return 0;
  
} 
