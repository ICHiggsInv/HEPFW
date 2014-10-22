#include "TFile.h"
#include "TH1.h"
#include "TH1I.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TPaveText.h"
#include "TLine.h"
#include "TGaxis.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <boost/algorithm/string.hpp>

#include "Plots/Style/interface/Style.h"
#include "FWCore/IO/interface/File.h"

#include <boost/algorithm/string.hpp>

using namespace std;

//#################################################################################
//#################################################################################
//#################################################################################
TCanvas* doCanvas(TH1D* sig,TH1D* bkg,TH1D* notETM,const char* name,const char* path,ostringstream &iStream){
  
  //const int nMaxBunch50ns = 1380;
  const int nMaxBunch25ns = 2808;
  const int ratePerBunch  = 11246;
  
  TCanvas *c0 = new TCanvas(Form("rates_%s",name));
  
  TPad *pad = new TPad("pad","",0,0,1,1);
  pad->SetFillColor(0);
  pad->SetGridx();
  pad->SetTicky(false);
  pad->Draw();
  pad->cd();
  
  if(string(name)=="l1t_etm"){sig->GetXaxis()->SetRangeUser(0,200);}
  if(string(name)=="dijet_pt0 "){sig->GetXaxis()->SetTitle("Leading Jet p_{#perp}");}
  
  sig->GetYaxis()->SetTitleOffset(1.5);
  sig->GetYaxis()->SetTitle("Signal Efficiency");
  sig->Draw();
  
  
  if(notETM){
    if(string(name)=="l1t_etm"){notETM->GetXaxis()->SetRangeUser(0,200);}
    if(string(name)=="dijet_pt0 "){notETM->GetXaxis()->SetTitle("Leading Jet p_{#perp}");}
    notETM->GetYaxis()->SetTitleOffset(1.5);
    notETM->SetTitle("Signal Efficiency");
    notETM->SetFillColor(kGreen);
    notETM->SetFillStyle(3001);
    notETM->Draw("same");
  }

  ///////////
  c0->cd();
  TPad *overlay = new TPad("overlay","",0,0,1,1);
  overlay->SetFillStyle(4000);
  overlay->SetFillColor(0);
  overlay->SetFrameFillStyle(4000);
  overlay->Draw();
  overlay->cd();
  overlay->SetLogy();
  overlay->SetGridy();
  overlay->SetTicky(false);
  
  TH1D * rate = (TH1D*) bkg->Clone(Form("rate_%s",sig->GetTitle()));
  if(string(name)=="l1t_etm"){rate->GetXaxis()->SetRangeUser(0,200);}
  if(string(name)=="dijet_pt0 "){rate->GetXaxis()->SetTitle("Leading Jet p_{#perp}");}
  // rate->GetYaxis()->SetRangeUser(1,1.2e7);
  rate->GetYaxis()->SetTitle("HLT Rate (Hz)");
  rate->Scale(ratePerBunch*nMaxBunch25ns);
  rate->SetLineColor(kRed);
  rate->GetYaxis()->SetAxisColor(kRed);
  rate->GetYaxis()->SetTitleColor(kRed);
  rate->GetYaxis()->SetLabelColor(kRed);
  rate->GetYaxis()->SetTitleOffset(1.5);  
  rate->Draw("Y+");
  
  TLegend *l = new TLegend(0.50,0.80,0.85,0.95);
  l->SetBorderSize(1);
  l->AddEntry(sig,"VBF Inv Eff");
  if(notETM){
    l->AddEntry(notETM,"VBF Inv Eff (not ETM70)");
  }
  l->AddEntry(rate, "Neutrino Gun Rate");
  l->Draw();
  
  //draw an axis on the right side
  //c0->SaveAs("PU40bx50_rate_DijetVBF30_L1TETM_logScale.pdf");  
  
  if(path==string("Run_1/DiffDijet/L1T_ETM60") && name==string("jets40_met_mindphi")){
    int theBin = sig->FindBin(1.0);
    iStream << "Run_1/DiffDijet/L1T_ETM60/jets40_met_mindphi sig eff:" << sig->GetBinContent(theBin) 
    << " sig not etm70:" << notETM->GetBinContent(theBin) << " rate:" << rate->GetBinContent(theBin) << " border:" << sig->GetXaxis()->GetBinLowEdge(theBin) << endl;
  }

  if(path==string("Run_1/DiffDijet/L1T_HTT70") && name==string("MHToverHTT ")){
    int theBin = sig->FindBin(0.7);
    iStream << "Run_1/DiffDijet/HTT70/L1T_HTT70 sig eff:" << sig->GetBinContent(theBin) 
    << " sig not etm70:" << notETM->GetBinContent(theBin) << " rate:" << rate->GetBinContent(theBin) << " border:" << sig->GetXaxis()->GetBinLowEdge(theBin) << endl;
  }
  
  
  for(int i=0; i<=sig->GetNbinsX()+1; i++){
    if(sig->GetBinContent(i)>=0.2 && rate->GetBinContent(i)<=5000){

      double valNotEtm = -1;
      if(notETM){valNotEtm = notETM->GetBinContent(i);}
      
      iStream << Form("| %40s | %20s | %7.2f | %4.0f | %5.3f | %5.3f |\n",
                   path,sig->GetName(),
                   sig->GetXaxis()->GetBinLowEdge(i),
                   rate->GetBinContent(i),
                   sig->GetBinContent(i),
                   valNotEtm);
      break;
    }
  }
  
  if(notETM){
  
    for(int i=0; i<=sig->GetNbinsX()+1; i++){
      if(notETM->GetBinContent(i)>=0.03 && rate->GetBinContent(i)<=5000){
        double valNotEtm = -1;
        if(notETM){valNotEtm = notETM->GetBinContent(i);}
        
        iStream << Form("| %40s | %20s | %7.2f | %4.0f | %5.3f | %5.3f |\n",
                     path,sig->GetName(),
                     sig->GetXaxis()->GetBinLowEdge(i),
                     rate->GetBinContent(i),
                     sig->GetBinContent(i),
                     valNotEtm);
        break;
      }
    }
  }
  
  
  
  return c0;
  
}

//#################################################################################
//#################################################################################
//#################################################################################
TCanvas* doHLTCanvas(TH1D* sig,TH1D* bkg,const char* name){
  
  TCanvas *c0 = new TCanvas(Form("rates_%s",name));
  
  TPad *pad = new TPad("pad","",0,0,1,1);
  pad->SetFillColor(0);
  pad->SetGridx();
  pad->SetTicky(false);
  pad->Draw();
  pad->cd();
  
  sig->GetYaxis()->SetTitleOffset(1.5);
  sig->GetYaxis()->SetTitle("Signal Efficiency");
  sig->Draw();
  
  ///////////
  c0->cd();
  TPad *overlay = new TPad("overlay","",0,0,1,1);
  overlay->SetFillStyle(4000);
  overlay->SetFillColor(0);
  overlay->SetFrameFillStyle(4000);
  overlay->Draw();
  overlay->cd();
  overlay->SetLogy();
  overlay->SetGridy();
  overlay->SetTicky(false);
  
  TH1D * rate = (TH1D*) bkg->Clone(Form("rate_%s",sig->GetTitle()));
  rate->GetYaxis()->SetTitle("HLT Rate (Hz)");
  rate->SetLineColor(kRed);
  rate->GetYaxis()->SetAxisColor(kRed);
  rate->GetYaxis()->SetTitleColor(kRed);
  rate->GetYaxis()->SetLabelColor(kRed);
  rate->GetYaxis()->SetTitleOffset(1.5);  
  rate->Draw("Y+");
  
  TLegend *l = new TLegend(0.50,0.80,0.85,0.95);
  l->SetBorderSize(1);
  l->AddEntry(sig,"VBF Inv Eff");
  l->AddEntry(rate,"QCD Rate");
  l->Draw();

  return c0;
  
}

//#################################################################################
//#################################################################################
//#################################################################################
void l1tAnalysis(){
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  hepfw::File *fOut = new hepfw::File("L1AlgoWPStudiesResults_PU40bx25_eff.root","RECREATE");
  
  hepfw::File *fSig = new hepfw::File("L1AlgoWPStudiesResults_L1TEmuStage1_VBFInv_PU40bx25.root");
  hepfw::File *fBkg = new hepfw::File("L1AlgoWPStudiesResults_L1TEmuStage1_NeutrinoGun_PU40bx25.root");
  
  vector<TH1*> hSig = fSig->getHistograms();
  vector<TH1*> hBkg = fBkg->getHistograms();
  
  TH1I* hSigTotal = (TH1I*) fSig->Get("Run_1/EventCount");
  double nSigEvents = hSigTotal->GetBinContent(1);
  
  TH1I* hBkgTotal = (TH1I*) fBkg->Get("Run_1/EventCount");
  double nBkgEvents = hBkgTotal->GetBinContent(1);
  
  fOut->copyDirectoryStructure(fSig);
  fOut->Write();
  
  ostringstream myStream;
  myStream << "| *Base Cut* | *Variable Cut* | *Variable Value* | *Rate* | *Sig Eff* | *Sig Eff (NOT ETM70)* |" << endl;
  
  for(unsigned s=0; s<hSig.size(); s++){
    
    TH1D *pSig = (TH1D*) hSig[s];
    
    string sigTitle = pSig->GetName();
    string sigPath  = pSig->GetDirectory()->GetPath();
    sigPath  = sigPath.substr(sigPath.find(':')+2,sigPath.size()-1);
    
    for(unsigned b=0; b<hBkg.size(); b++){
      
      TH1D *pBkg = (TH1D*) hBkg[b];
      
      string bkgTitle = pBkg->GetName();
      string bkgPath  = pBkg->GetDirectory()->GetPath();
      bkgPath = bkgPath.substr(bkgPath.find(':')+2,bkgPath.size()-1);
      
      if(sigTitle == bkgTitle && sigPath == bkgPath){
        
        //cout << "Plot: " << sigPath << " name: " << pSig->GetName() << " title: " << pSig->GetTitle() << endl;
        
        TH1D *pSigEff   = (TH1D*) pSig->Clone(Form("Sig_%s_eff",pSig->GetName()));
        TH1D *pBkgEff   = (TH1D*) pBkg->Clone(Form("Bkg_%s_eff",pBkg->GetName()));
        
        TH1D *pNoETM    = 0;
        TH1D *pNoETMEff = 0;
        if(sigPath.find("SameDijet")!=std::string::npos){
          
          string nameSameDijet = Form("%s/%s",sigPath.c_str(),sigTitle.c_str());
          
          boost::replace_all(nameSameDijet,"SameDijet","SameDijetNotETM70");
          pNoETM = (TH1D*) fSig->Get(nameSameDijet.c_str());
          
          if(pNoETM){
            pNoETMEff = (TH1D*) pNoETM->Clone(Form("ETM_%s_eff",pBkg->GetName()));
          }
        }
        
        if(sigPath.find("DiffDijet")!=std::string::npos){
          
          string nameSameDijet = Form("%s/%s",sigPath.c_str(),sigTitle.c_str());
          
          boost::replace_all(nameSameDijet,"DiffDijet","SameDijetNotETM70");
          pNoETM = (TH1D*) fSig->Get(nameSameDijet.c_str());
          
          if(pNoETM){
            pNoETMEff = (TH1D*) pNoETM->Clone(Form("ETM_%s_eff",pBkg->GetName()));
          }
        }
        
        bool reverseIntegral = false;
        
        // Plots that cut will be 'less than' so integral must be reversed
        if(string(pSig->GetName()).find("dijet_dphi")   != std::string::npos){reverseIntegral=true;}
        if(string(pSig->GetName()).find("jets_mindphi") != std::string::npos){reverseIntegral=true;}
        if(string(pSig->GetName()).find("jets_met_maxdphi") != std::string::npos){reverseIntegral=true;}
        
        if(reverseIntegral){
          for(int i=0; i<=pSigEff->GetNbinsX()+1; i++){pSigEff->SetBinContent(i,pSig->Integral(0,i));}
          for(int i=0; i<=pBkgEff->GetNbinsX()+1; i++){pBkgEff->SetBinContent(i,pSig->Integral(0,i));}
          
          if(pNoETMEff){
            for(int i=0; i<=pNoETMEff->GetNbinsX()+1; i++){pNoETMEff->SetBinContent(i,pNoETM->Integral(0,i));}
          }
        }else{
          for(int i=0; i<=pSigEff->GetNbinsX()+1; i++){pSigEff->SetBinContent(i,pSigEff->Integral(i,pSigEff->GetNbinsX()+1));}
          for(int i=0; i<=pBkgEff->GetNbinsX()+1; i++){pBkgEff->SetBinContent(i,pBkgEff->Integral(i,pBkgEff->GetNbinsX()+1));}
          
          if(pNoETMEff){
            for(int i=0; i<=pNoETMEff->GetNbinsX()+1; i++){pNoETMEff->SetBinContent(i,pNoETM->Integral(i,pSigEff->GetNbinsX()+1));}
          }
        }
        pSigEff  ->Scale(1/nSigEvents);
        pBkgEff  ->Scale(1/nBkgEvents);
        if(pNoETMEff){pNoETMEff->Scale(1/nSigEvents);}
        
        TCanvas* c = doCanvas(pSigEff,pBkgEff,pNoETMEff,pSig->GetName(),sigPath.c_str(),myStream);
        
        TDirectoryFile *d = (TDirectoryFile*) fOut->Get(sigPath.c_str());
        d->WriteTObject(c);
        
        system(Form("mkdir -p %s",sigPath.c_str()));
        c->SaveAs(Form("%s/%s.%s",sigPath.c_str(),pSig->GetName(),"png"));
        
        delete pSigEff;
        delete pBkgEff;
        delete pNoETMEff;
        delete c;
        
        break;
      }
    }  
    
  }
  
  cout << "L1AlgoWPStudiesResults_VBFInv_PU40bx25.root      has " << hSig.size() << " histograms!" << endl;
  cout << "L1AlgoWPStudiesResults_NeutrinoGun_PU40bx25.root has " << hBkg.size() << " histograms!" << endl;
  
  cout << myStream.str();
  
  fOut->Write();
  
}

//#################################################################################
//#################################################################################
//#################################################################################
void hltAnalysis(){
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();

  double targetLumi = 1.4e34;
  
  // Getting VBF Higgs invisible signal and neutrino gun
  hepfw::File *fSig   = new hepfw::File("PU40bx25_VBFInv.root");
  hepfw::File *fNugun = new hepfw::File("PU40bx25_NeutrinoGun.root");

  // Getting QCD samples
  map<string,hepfw::File*> fQCD;
  fQCD["QCD_Pt-30to50"]     = new hepfw::File("PU40bx25_QCD_Pt-30to50.root");
  fQCD["QCD_Pt-50to80"]     = new hepfw::File("PU40bx25_QCD_Pt-50to80.root");
  fQCD["QCD_Pt-80to120"]    = new hepfw::File("PU40bx25_QCD_Pt-80to120.root");
  fQCD["QCD_Pt-120to170"]   = new hepfw::File("PU40bx25_QCD_Pt-120to170.root");
  fQCD["QCD_Pt-170to300"]   = new hepfw::File("PU40bx25_QCD_Pt-170to300.root");
  fQCD["QCD_Pt-300to470"]   = new hepfw::File("PU40bx25_QCD_Pt-300to470.root");
  fQCD["QCD_Pt-470to600"]   = new hepfw::File("PU40bx25_QCD_Pt-470to600.root");
  fQCD["QCD_Pt-600to800"]   = new hepfw::File("PU40bx25_QCD_Pt-600to800.root");
  fQCD["QCD_Pt-800to1000"]  = new hepfw::File("PU40bx25_QCD_Pt-800to1000.root");
  fQCD["QCD_Pt-1000to1400"] = new hepfw::File("PU40bx25_QCD_Pt-1000to1400.root");
  fQCD["QCD_Pt-1400to1800"] = new hepfw::File("PU40bx25_QCD_Pt-1400to1800.root");

  // Creating output file and replicating directory structure
  hepfw::File *fOut = new hepfw::File("PU40bx25_HLTAnalysis_eff.root","RECREATE");
  fOut->copyDirectoryStructure(fSig);
  fOut->Write();
  
  // Cross sections in [pb] as reported in mcm
  map<string,double> xsec;
  xsec["QCD_Pt-30to50"]     = 161500000;
  xsec["QCD_Pt-50to80"]     =  22110000;
  xsec["QCD_Pt-80to120"]    =   3000114.3;
  xsec["QCD_Pt-120to170"]   =    493200;
  xsec["QCD_Pt-170to300"]   =    120300;
  xsec["QCD_Pt-300to470"]   =      7475;
  xsec["QCD_Pt-470to600"]   =       587.1;
  xsec["QCD_Pt-600to800"]   =       167;
  xsec["QCD_Pt-800to1000"]  =       28.25;
  xsec["QCD_Pt-1000to1400"] =        8.195;
  xsec["QCD_Pt-1400to1800"] =        0.7346;
  
  TH1I* hSigTotal = (TH1I*) fSig->Get("EventCount");
  double nSigEvents = hSigTotal->GetBinContent(1);
  
  //   TH1I* hNuGunTotal = (TH1I*) fNugun->Get("EventCount");
  //   double nBkgEvents = hNuGunTotal->GetBinContent(1);
  
  
  map<string,double> nQCDEvents;
  for(auto i=fQCD.begin(); i!=fQCD.end(); i++){
    TH1I* hEv = (TH1I*) i->second->Get("EventCount");
    nQCDEvents[i->first]= hEv->GetBinContent(1);
    printf("Sample: %40s event: %.0f\n",i->first.c_str(),hEv->GetBinContent(1));
  }
  
  vector<TH1*> hSig   = fSig  ->getHistograms();
  vector<TH1*> hNuGun = fNugun->getHistograms();
  
  map<string,vector<TH1*> > hQCD;
  for(auto i=fQCD.begin(); i!=fQCD.end(); i++){
    cout << "Getting all histograms for: " << i->first << endl;
    hQCD[i->first] = i->second->getHistograms();
  }


  //################################################################################
  
  // Looping over all histograms of the signal
  for(unsigned iSig=0; iSig<hSig.size(); iSig++){
    
    TH1D *pSig = (TH1D*) hSig[iSig];
    
    // Getting name and path (file name subtracted) of the histogram
    string sigTitle = pSig->GetName();
    string sigPath  = pSig->GetDirectory()->GetPath();
    sigPath  = sigPath.substr(sigPath.find(':')+2,sigPath.size()-1);
    
    TH1D* totalBkg = 0;
    
    for(auto iSample=hQCD.begin(); iSample!=hQCD.end(); iSample++){
      
      vector<TH1*> thisPlots = iSample->second;
      
      for(unsigned iPlot=0; iPlot<thisPlots.size(); iPlot++){
        
        TH1 *pBkg = (TH1*) thisPlots[iPlot];
        
        // Getting name and path (file name subtracted) of the histogram
        string bkgTitle = pBkg->GetName();
        string bkgPath  = pBkg->GetDirectory()->GetPath();
        bkgPath = bkgPath.substr(bkgPath.find(':')+2,bkgPath.size()-1);
        
        if(sigTitle == bkgTitle && sigPath == bkgPath){

          TH1D *pBkgEff = (TH1D*) pBkg->Clone(Form("Bkg_%s_eff",pBkg->GetName()));
          
          // Computing integral from each bin to infinity
          for(int i=0; i<=pBkgEff->GetNbinsX()+1; i++){pBkgEff->SetBinContent(i,pBkgEff->Integral(i,pBkgEff->GetNbinsX()+1));}
          
          // Normalising to 1 over total event processed
          pBkgEff->Scale(1/nQCDEvents[iSample->first]);
          
          // Scaling by the total rate of the sample
          pBkgEff->Scale(xsec[iSample->first]*(targetLumi*1e-36));
          
          if(totalBkg==0){
            // First time adding plot
            totalBkg = pBkgEff;
          }else{
            // Adding to an existing plot
            totalBkg->Add(pBkgEff);
            delete pBkgEff;
          }
          break;
        }
      }
    }
    
    TH1D *pSigEff = (TH1D*) pSig->Clone(Form("Sig_%s_eff",pSig->GetName()));
    
    // Computing integral from each bin to infinity
    for(int x=0; x<=pSigEff->GetNbinsX()+1; x++){pSigEff->SetBinContent(x,pSigEff->Integral(x,pSigEff->GetNbinsX()+1));}
    pSigEff->Scale(1/nSigEvents);
    
    TCanvas* c = doHLTCanvas(pSigEff,totalBkg,pSig->GetName());
    
    if(sigPath==""){
      fOut->WriteTObject(c);
    }else{
      TDirectoryFile *d = (TDirectoryFile*) fOut->Get(sigPath.c_str());
      d->WriteTObject(c);
    }
    system(Form("mkdir -p %s",sigPath.c_str()));
    c->SaveAs(Form("%s/%s.%s",sigPath.c_str(),pSig->GetName(),"png"));
    
    delete pSigEff;
    delete totalBkg;
    delete c;
  }
}

//#################################################################################
//#################################################################################
//#################################################################################
int main(int argc, char *argv[]){

  // Caching command line parameters
  bool doL1T = false;
  bool doHLT = false;
  
  bool incorrectCmd = false;
  if(argc!=2){incorrectCmd=true;}
    else{
    if      (!strcmp(argv[1],"--l1t")){doL1T=true;}
    else if (!strcmp(argv[1],"--hlt")){doHLT=true;}
    else{incorrectCmd=true;}
  }
  
  if(incorrectCmd){
    printf("Usage: %s [option]\n", argv[0]);
    printf("Possible options:\n");
    printf("--l1t : Do L1T Analysis\n");
    printf("--hlt : Do HLT Analysis\n");
    return 0;
  }
  
  
  if(doL1T){l1tAnalysis();}
  if(doHLT){hltAnalysis();}

  return 0;
  
};