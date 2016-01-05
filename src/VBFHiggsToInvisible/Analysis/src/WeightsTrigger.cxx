#include "VBFHiggsToInvisible/Analysis/interface/WeightsTrigger.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/PileupInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/Candidate.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

using namespace std;

hepfw::WeightsTrigger::WeightsTrigger(){
  m_name = "";
}

hepfw::WeightsTrigger::WeightsTrigger(std::string name){
  m_name = name;
}

void hepfw::WeightsTrigger::beginJob(hepfw::JobSetup &job){
  
}

hepfw::WeightsTrigger::WeightsTrigger(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  m_name = name;
  
  triggerSF_ = new TFile("/vols/cms02/jca10/work/slc6/dev01/cc/HEPFW_v2/src/VBFHiggsToInvisible/Analysis/data/Weights/trigger/HLTEffParkedABCD_MET1DFit.root");

  binnedin2d1dfitweightvarorder_.push_back("Jet");
  binnedin2d1dfitweightvarorder_.push_back("Mjj");
  binnedin2d1dfitweightvarorder_.push_back("MET");
  
  binnedin2d1dfitweightvar1binning_.push_back(30);
  binnedin2d1dfitweightvar1binning_.push_back(40);
  binnedin2d1dfitweightvar1binning_.push_back(50);
  binnedin2d1dfitweightvar1binning_.push_back(60);
  binnedin2d1dfitweightvar1binning_.push_back(1000);
  
  binnedin2d1dfitweightvar2binning_.push_back(0);
  binnedin2d1dfitweightvar2binning_.push_back(600);
  binnedin2d1dfitweightvar2binning_.push_back(800);
  binnedin2d1dfitweightvar2binning_.push_back(900);
  binnedin2d1dfitweightvar2binning_.push_back(1000);
  binnedin2d1dfitweightvar2binning_.push_back(5000);
  
  std::cout<<"Getting trigger efficiency functions"<<std::endl;
  for(unsigned iVar1=0;iVar1<(binnedin2d1dfitweightvar1binning_.size()-1);iVar1++){
    std::vector<std::vector<TF1*> > thisfuncvectorvector;
    for(unsigned iVar2=0;iVar2<(binnedin2d1dfitweightvar2binning_.size()-1);iVar2++){
      std::vector<TF1*> thisfuncvector;
      std::ostringstream convert;
      convert<<iVar1+1<<iVar2+1;
      std::string histnumber=convert.str();
      thisfuncvector.push_back((TF1*)triggerSF_->Get(("fData_"+binnedin2d1dfitweightvarorder_[2]+"_1D_"+histnumber+"A").c_str()));
      thisfuncvector.push_back((TF1*)triggerSF_->Get(("fData_"+binnedin2d1dfitweightvarorder_[2]+"_1D_"+histnumber+"BC").c_str()));
      thisfuncvector.push_back((TF1*)triggerSF_->Get(("fData_"+binnedin2d1dfitweightvarorder_[2]+"_1D_"+histnumber+"D").c_str()));
      thisfuncvectorvector.push_back(thisfuncvector);
    }
    func_trigSF_binnedin2d.push_back(thisfuncvectorvector);
  }
  std::cout<<"  done."<<std::endl;

}

hepfw::WeightsTrigger::~WeightsTrigger(){
  
}

void hepfw::WeightsTrigger::produce(hepfw::Event &event){
  
  //double Alumi_  = -1;
  //double BClumi_ = -1;
  //double Dlumi_  = -1; //7.315
  
  double Alumi_  = 0.889;
  double BClumi_ = 11.023;
  double Dlumi_  = 7.315; //7.317 correct
  
  ic::Met *metHLT = event.getByName<ic::Met>("pfMet_subtractedMuonTight");
  ic::Met *metL1  = event.getByName<ic::Met>("pfMet_subtractedMuonTight");
  
  double l1met  = metL1->pt();
  double hltmet = metHLT->pt();
  
  double mjj=0.;
  double jet1pt=0.;
  double jet2pt=0.;
  
  vector<ic::PFJet>* jets = event.getByName< vector<ic::PFJet> >("cleanPFJets");

  if(jets->size()>=2){
    
    // Assuming jet collection is sorted
    ic::PFJet *j0 = &(*jets)[0];
    ic::PFJet *j1 = &(*jets)[1];
    
    double px = j0->vector().px() + j1->vector().px();
    double py = j0->vector().py() + j1->vector().py();
    double pz = j0->vector().pz() + j1->vector().pz();
    double normaP = pow(px,2) + pow(py,2) + pow(pz,2);
    
    mjj = sqrt(pow(j0->energy()+j1->energy(),2) - normaP);
    jet1pt = j0->pt();
    jet2pt = j1->pt();
    
    if(l1met!=hltmet){
      std::cout<<"Error: you must use metnomuons for both l1met and hltmet"<<std::endl;
      return;
    }
    double vars[3];
    bool found[3]={false};
    //Get the 3 variables
    for(unsigned iVar=0;iVar<binnedin2d1dfitweightvarorder_.size();iVar++){
      if(binnedin2d1dfitweightvarorder_[iVar]=="MET"){
        vars[iVar]=hltmet;
        found[0]=true;
      }
      if(binnedin2d1dfitweightvarorder_[iVar]=="Mjj"){
        vars[iVar]=mjj;
        found[1]=true;
      }
      if(binnedin2d1dfitweightvarorder_[iVar]=="Jet"){
        vars[iVar]=jet2pt;
        found[2]=true;
      }
    }
    if(!((found[0]==true)&&(found[1]==true)&&(found[2]==true))){
      std::cout<<"You must specify MET,Mjj and Jet as the variables used for 2d binned 1d trigger weights"<<std::endl;
      return;
    }
    //FIND WHICH BIN YOU'RE IN
    int var1bin=-10;
    int var2bin=-10;
    if(vars[0]<binnedin2d1dfitweightvar1binning_[0])var1bin=-1;
    else{
      for(unsigned iBin=0;iBin<(binnedin2d1dfitweightvar1binning_.size()-1);iBin++){
        if(vars[0]<binnedin2d1dfitweightvar1binning_[iBin+1]){
          var1bin=iBin+1;
          break;
        }
      }     
      if(var1bin==-10)var1bin=binnedin2d1dfitweightvar1binning_.size()-1;
    }
    if(vars[1]<binnedin2d1dfitweightvar1binning_[0])var2bin=-1;
    else{
      for(unsigned iBin=0;iBin<(binnedin2d1dfitweightvar2binning_.size()-1);iBin++){
        if(vars[1]<binnedin2d1dfitweightvar2binning_[iBin+1]){
          var2bin=iBin+1;
          break;
        }
      }
      if(var2bin==-10)var2bin=binnedin2d1dfitweightvar2binning_.size()-1;
    }
    double trgweights[3];
    if((var1bin!=-1)&&(var2bin!=-1)){
      //!!READ OUT WEIGHT FOR EACH RUN
      double xmin,xmax;
      TF1* funcs[3];
      for(unsigned iRun=0;iRun<3;iRun++){
        funcs[iRun]=func_trigSF_binnedin2d[var1bin-1][var2bin-1][iRun];
      }
      funcs[0]->GetRange(xmin,xmax);
      
      //Get weight                                                                                                                                     
      for(unsigned iRun=0;iRun<3;iRun++){
        
        if(vars[2]<=xmax){
          if(vars[2]>=xmin){
            trgweights[iRun]=funcs[iRun]->Eval(vars[2]);
          }
          else trgweights[iRun]=0;
        }
        else trgweights[iRun]=funcs[iRun]->Eval(xmax);
      }
    }
    else{
      for(unsigned iRun=0;iRun<3;iRun++){
        trgweights[iRun]=0;
      }
    }
    //LUMI WEIGHTED AVERAGE OVER RUNS                                                                                                      
    double trgweight=(trgweights[0]*Alumi_+trgweights[1]*BClumi_+trgweights[2]*Dlumi_)/(Alumi_+BClumi_+Dlumi_);
    //std::cout<<" Total Weight "<<trgweight<<std::endl;                                                                                            
    //SET TRIGGER WEIGHT                                                                                                                             
    event.addWeight("weight_Trigger",trgweight);
  }
}
