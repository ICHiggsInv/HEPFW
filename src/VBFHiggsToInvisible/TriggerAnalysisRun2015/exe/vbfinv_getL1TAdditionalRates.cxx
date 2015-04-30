#include "FWCore/IO/interface/File.h"
#include "Plots/Style/interface/Style.h"
#include "Latex/Table/interface/LatexTable.h"
#include "Latex/Table/interface/LatexTabular.h"
#include "Latex/Table/interface/LatexCaption.h"

#include "TH1I.h"
#include "TH1D.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//####################################################################
int main(int argc, char *argv[]){
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  hepfw::File *fSig = new hepfw::File("L1TAdditionalRateStudiesResults_job0.root");
  
  
  TH1I *hE = (TH1I*) fSig->Get("Menu");
  TH1I *hT = (TH1I*) fSig->Get("EventCount");
  
  TH1D* hRatePrePS = (TH1D*) fSig->Get("Algos/algoCountsPrePS");
  TH1D* hRatePosPS = (TH1D*) fSig->Get("Algos/algoCountsPostPS");
  TH1D* hRatePure  = (TH1D*) fSig->Get("Algos/algoCountsPure");
  
  hepfw::LatexTable table0;
  table0.setCentering(true);
  table0.setPosition("htp");
  table0.setLabel   ("tableTest01");
  
  hepfw::LatexTabular tabular0(129,4);
  tabular0.setTabularPrecision(".0");
  tabular0.setColumnDecorationBefore(0,"|");
  tabular0.setColumnDecorationBefore(1,"||");
  tabular0.setColumnDecorationBefore(2,"|");
  tabular0.setColumnDecorationBefore(3,"|");
  tabular0.setColumnDecorationAfter (3,"|");
  
  tabular0.setColumnAlignment(0,"l");
  tabular0.setColumnAlignment(1,"r");
  tabular0.setColumnAlignment(2,"r");
  tabular0.setColumnAlignment(3,"r");
  
  tabular0.setRowDecorationBefore(0,"\\hline");
  tabular0.setRowDecorationBefore(1,"\\hline \\hline");
  
  tabular0.setCellContent(0,0,"Algo");
  tabular0.setCellContent(0,1,"Before PS Rate [Hz]");
  tabular0.setCellContent(0,2,"After PS Rate [Hz]");
  tabular0.setCellContent(0,3,"Pure Rate [Hz]");
  
  for(int i=1; i<=128; i++){
    tabular0.setCellContent(i,0,hRatePrePS->GetXaxis()->GetBinLabel(i));
    tabular0.setCellContent(i,1,hRatePrePS->GetBinContent(i)/hT->GetBinContent(1)*11246*2808);
    tabular0.setCellContent(i,2,hRatePosPS->GetBinContent(i)/hT->GetBinContent(1)*11246*2808);
    tabular0.setCellContent(i,3,hRatePure ->GetBinContent(i)/hT->GetBinContent(1)*11246*2808);
  }

  tabular0.setRowDecorationAfter(128,"\\hline");
  
  table0.innerObjects.push_back(&tabular0);
  
  hepfw::LatexCaption caption("L1T Rates");
  table0.innerObjects.push_back(&caption);
  
  table0.saveAs("text0.tex");

  cout << "Events processed           : " << hT->GetBinContent(1) << endl;
  cout << "L1T Rate [Hz]              : " << (hE->GetBinContent(1)/hT->GetBinContent(1))*11246*2808 << " +/- " << (sqrt(hE->GetBinContent(1))/hT->GetBinContent(1))*11246*2808 << endl;
  cout << "L1T_ETM70 Rate [Hz]        : " << (hE->GetBinContent(2)/hT->GetBinContent(1))*11246*2808 << " +/- " << (sqrt(hE->GetBinContent(2))/hT->GetBinContent(1))*11246*2808 << endl;
  cout << "L1T_ETM70 Pure Rate [Hz]   : " << (hE->GetBinContent(3)/hT->GetBinContent(1))*11246*2808 << " +/- " << (sqrt(hE->GetBinContent(3))/hT->GetBinContent(1))*11246*2808 << endl;
  cout << "Dijet_ETM50 Rate [Hz]      : " << (hE->GetBinContent(4)/hT->GetBinContent(1))*11246*2808 << " +/- " << (sqrt(hE->GetBinContent(4))/hT->GetBinContent(1))*11246*2808 << endl;
  cout << "Dijet_ETM50 Pure Rate [Hz] : " << (hE->GetBinContent(5)/hT->GetBinContent(1))*11246*2808 << " +/- " << (sqrt(hE->GetBinContent(5))/hT->GetBinContent(1))*11246*2808 << endl;
  cout << "Dijet_Jet96 Rate [Hz]      : " << (hE->GetBinContent(6)/hT->GetBinContent(1))*11246*2808 << " +/- " << (sqrt(hE->GetBinContent(6))/hT->GetBinContent(1))*11246*2808 << endl;
  cout << "Dijet_Jet96 Pure Rate [Hz] : " << (hE->GetBinContent(7)/hT->GetBinContent(1))*11246*2808 << " +/- " << (sqrt(hE->GetBinContent(7))/hT->GetBinContent(1))*11246*2808 << endl;
  
  return 0;

};