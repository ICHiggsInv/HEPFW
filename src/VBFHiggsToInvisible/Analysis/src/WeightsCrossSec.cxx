#include "VBFHiggsToInvisible/Analysis/interface/WeightsCrossSection.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"

using namespace std;

hepfw::WeightsCrossSection::WeightsCrossSection(){
  m_name = "";
}

hepfw::WeightsCrossSection::WeightsCrossSection(std::string name){
  m_name = name;
}

void hepfw::WeightsCrossSection::beginJob(hepfw::JobSetup &job){
  
  TDirectory* thisDir = job.getDirectoryModules()->mkdir(m_name.c_str());
  
  tighteleweight = new TH1F("tighteleweight","tighteleweight",2000,0.,2.); tighteleweight->SetDirectory(thisDir);
  tightmuweight  = new TH1F("tightmuweight", "tightmuweight", 2000,0.,2.); tightmuweight ->SetDirectory(thisDir);
  vetoeleweight  = new TH1F("vetoeleweight", "vetoeleweight", 2000,0.,2.); vetoeleweight ->SetDirectory(thisDir);
  vetomuweight   = new TH1F("vetomuweight",  "vetomuweight",  2000,0.,2.); vetomuweight  ->SetDirectory(thisDir);
  
}

hepfw::WeightsCrossSection::WeightsCrossSection(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  m_name = name;
  
  string datasetName = dataset.getName();
  
  double intLumi                   = pset.getParameter<double>          ("intLumi");
  map<string,double> sampleDetails = pset.getParameterMap<string,double>(datasetName);
  
  double sampleXSec    = sampleDetails["crossSection"];
  double sampleNEvents = sampleDetails["events"];
  m_weightXSec = sampleXSec*intLumi/sampleNEvents;
  /*
  cout << "[hepfw::WeightsCrossSection] Dataset name             = " << datasetName << endl;
  cout << "[hepfw::WeightsCrossSection] Instant Luminosity       = " << intLumi << endl;
  cout << "[hepfw::WeightsCrossSection] Dataset cross section    = " << sampleXSec << endl;
  cout << "[hepfw::WeightsCrossSection] Dataset processed events = " << sampleNEvents << endl;
  cout << "[hepfw::WeightsCrossSection] Sample weight is         = " << m_weightXSec << endl;
  
  if (datasetName.find("JetsToLNu") != datasetName.npos) {
    xsWeights.set_do_w_soup(true);
    xsWeights.set_do_w_reweighting(false);
    
    if (mc == mc::summer12_53X) {
      xsWeights.SetWTargetFractions(0.74069073, 0.1776316, 0.0575658, 0.0170724, 0.00703947);
      xsWeights.SetWInputYields(76102995.0, 23141598.0, 34044921.0, 15539503.0, 13382803.0);
      //xsWeights.SetWInputYields(76102995.0, 23141598.0, 33901569.0, 15539503.0, 13382803.0);
    }
  }
  if (datasetName.find("JetsToLL") != datasetName.npos && 
    datasetName.find("PtZ-100-madgraph") == datasetName.npos && 
    datasetName.find("DYJJ01") == datasetName.npos) {
    if (mc == mc::summer12_53X) {
      xsWeights.set_do_dy_soup(true);
      xsWeights.set_do_dy_reweighting(false);
      xsWeights.SetDYTargetFractions(0.723342373, 0.190169492, 0.061355932, 0.017322034, 0.007810169);
      if(prod=="Apr04"){
        xsWeights.SetDYInputYields(30459503.0, 23970248.0, 21852156.0, 11015445.0, 6402827.0);
      }
      else{
        xsWeights.SetDYInputYields(30459503.0, 24045248.0, 21852156.0, 11015445.0, 6402827.0);
      }
    }
    }
  
  
  if (do_w_soup_) {
    std::cout << "Making W Soup:" << std::endl;
    std::cout << "nInc = " << n_inc_ << std::endl;
    w1_ = (n_inc_*f1_) / ( (n_inc_*f1_) + n1_ );
    w2_ = (n_inc_*f2_) / ( (n_inc_*f2_) + n2_ );
    w3_ = (n_inc_*f3_) / ( (n_inc_*f3_) + n3_ );
    w4_ = (n_inc_*f4_) / ( (n_inc_*f4_) + n4_ );
    std::cout << "f1 = " << f1_ << "\t" << "n1 = " << n1_ << "\t" << "w1 = " << w1_ << std::endl;
    std::cout << "f2 = " << f2_ << "\t" << "n2 = " << n2_ << "\t" << "w2 = " << w2_ << std::endl;
    std::cout << "f3 = " << f3_ << "\t" << "n3 = " << n3_ << "\t" << "w3 = " << w3_ << std::endl;
    std::cout << "f4 = " << f4_ << "\t" << "n4 = " << n4_ << "\t" << "w4 = " << w4_ << std::endl;
  }
  if (do_dy_soup_) {
    std::cout << "Making DY Soup:" << std::endl;
    std::cout << "nInc = " << zn_inc_ << std::endl;
    zw1_ = (zn_inc_*zf1_) / ( (zn_inc_*zf1_) + zn1_ );
    zw2_ = (zn_inc_*zf2_) / ( (zn_inc_*zf2_) + zn2_ );
    zw3_ = (zn_inc_*zf3_) / ( (zn_inc_*zf3_) + zn3_ );
    zw4_ = (zn_inc_*zf4_) / ( (zn_inc_*zf4_) + zn4_ );
    std::cout << "f1 = " << zf1_ << "\t" << "n1 = " << zn1_ << "\t" << "w1 = " << zw1_ << std::endl;
    std::cout << "f2 = " << zf2_ << "\t" << "n2 = " << zn2_ << "\t" << "w2 = " << zw2_ << std::endl;
    std::cout << "f3 = " << zf3_ << "\t" << "n3 = " << zn3_ << "\t" << "w3 = " << zw3_ << std::endl;
    std::cout << "f4 = " << zf4_ << "\t" << "n4 = " << zn4_ << "\t" << "w4 = " << zw4_ << std::endl;
  }*/
  
  
}

hepfw::WeightsCrossSection::~WeightsCrossSection(){
  
}

void hepfw::WeightsCrossSection::produce(hepfw::Event &event){
  
  event.addWeight("weightXSec",m_weightXSec);


  
  
}

void hepfw::WeightsCrossSection::SetWTargetFractions(double f0, double f1, double f2, double f3, double f4) {
  f0_ = f0;
  f1_ = f1;
  f2_ = f2;
  f3_ = f3;
  f4_ = f4;
  
}
void hepfw::WeightsCrossSection::SetWInputYields(double n_inc, double n1, double n2, double n3, double n4) {
  n_inc_ = n_inc;
  n1_ = n1;
  n2_ = n2;
  n3_ = n3;
  n4_ = n4;
}

void hepfw::WeightsCrossSection::SetDYTargetFractions(double zf0, double zf1, double zf2, double zf3, double zf4) {
  zf0_ = zf0;
  zf1_ = zf1;
  zf2_ = zf2;
  zf3_ = zf3;
  zf4_ = zf4;
  
}
void hepfw::WeightsCrossSection::SetDYInputYields(double zn_inc, double zn1, double zn2, double zn3, double zn4) {
  zn_inc_ = zn_inc;
  zn1_ = zn1;
  zn2_ = zn2;
  zn3_ = zn3;
  zn4_ = zn4;
}
