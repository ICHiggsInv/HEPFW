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
  
  cout << "[hepfw::WeightsCrossSection] Dataset name             = " << datasetName << endl;
  cout << "[hepfw::WeightsCrossSection] Instant Luminosity       = " << intLumi << endl;
  cout << "[hepfw::WeightsCrossSection] Dataset cross section    = " << sampleXSec << endl;
  cout << "[hepfw::WeightsCrossSection] Dataset processed events = " << sampleNEvents << endl;
  cout << "[hepfw::WeightsCrossSection] Sample weight is         = " << m_weightXSec << endl;
  
}

hepfw::WeightsCrossSection::~WeightsCrossSection(){
  
}

void hepfw::WeightsCrossSection::produce(hepfw::Event &event){
  
  event.addWeight("weight_XSec",m_weightXSec);


  
  
}

