#include "AnalysisTools/CutFlows/interface/AnalysisCutFlow.h"

using namespace std;

hepfw::AnalysisCutFlow::AnalysisCutFlow(){
  this->init();
}

hepfw::AnalysisCutFlow::AnalysisCutFlow(string name){
  this->init();
  m_name = name;
}

hepfw::AnalysisCutFlow::~AnalysisCutFlow(){
  
  // Deleting cuts
  // WARNING: This may lead to seg fault since same cut can be in multiple cut flows
  for(unsigned i=0; i<m_cutFlow.size(); i++){
    //delete m_cutFlow[i];
  }
}

void hepfw::AnalysisCutFlow::init(){
  m_name                 = "";
  m_eventYieldsDirectory = 0;
  m_eventYields_Absolute = 0;
  m_eventYields_Weighted = 0;
}

void hepfw::AnalysisCutFlow::setEventYieldDirectory(TDirectory* dir){
  m_eventYieldsDirectory = dir;
}

std::string hepfw::AnalysisCutFlow::getName(){
  return m_name;
}

void hepfw::AnalysisCutFlow::addAnalysisCut(hepfw::AnalysisCut* cut){
  
  m_cutFlow.push_back(cut);
  
  // Deleting previous yields if existing
  if(m_eventYields_Absolute){
    
    // If the histogram already exists and has entries produce an error message
    if(m_eventYields_Absolute->GetEntries()>0){
      cout << "[hepfw::AnalysisCutFlow::addAnalysisCut] ERROR: AnalysisCutFlow with name="
           << this->getName()
           << " absolute event yield has been deleted with "
           << m_eventYields_Absolute->GetEntries()
           << " entries." << endl;
    }
    delete m_eventYields_Absolute;
  }
  if(m_eventYields_Weighted){
    // If the histogram already exists and has entries produce an error message
    if(m_eventYields_Weighted->GetEntries()>0){
      cout << "[hepfw::AnalysisCutFlow::addAnalysisCut] ERROR: AnalysisCutFlow with name="
           << this->getName()
           << " weighted event yield has been deleted with "
           << m_eventYields_Weighted->GetEntries()
           << " entries."<< endl;
    }
    delete m_eventYields_Weighted;
  }
  
  // Creating new histograms with the extra cut
  string nameEvYiAbs = Form("EventYield_Absolute_%s",this->getName().c_str());
  string nameEvYiWgt = Form("EventYield_Weighted_%s",this->getName().c_str());
  m_eventYields_Absolute = new TH1D(nameEvYiAbs.c_str(),nameEvYiAbs.c_str(),m_cutFlow.size(),-0.5,m_cutFlow.size()-0.5);
  m_eventYields_Weighted = new TH1D(nameEvYiWgt.c_str(),nameEvYiWgt.c_str(),m_cutFlow.size(),-0.5,m_cutFlow.size()-0.5);

  // Filling bins label
  for(unsigned i=0; i<m_cutFlow.size(); i++){
    m_eventYields_Absolute->GetXaxis()->SetBinLabel(i,m_cutFlow[i]->getName().c_str());
    m_eventYields_Weighted->GetXaxis()->SetBinLabel(i,m_cutFlow[i]->getName().c_str());
  }

  // If the output directory is defined put histograms there
  if(m_eventYieldsDirectory){
    m_eventYields_Absolute->SetDirectory(m_eventYieldsDirectory);
    m_eventYields_Weighted->SetDirectory(m_eventYieldsDirectory);
  }
}

bool hepfw::AnalysisCutFlow::evaluate(hepfw::Event &event){
  
  for(unsigned i=0; i<m_cutFlow.size(); i++){
    if(m_cutFlow[i]->evaluate(event)){
      m_eventYields_Absolute->Fill(i);
      m_eventYields_Weighted->Fill(i); //TODO: Implement weights
    }else{
      return false;
    }
  }
  return true;
}

void hepfw::AnalysisCutFlow::setName(std::string name){
  m_name = name;
}
