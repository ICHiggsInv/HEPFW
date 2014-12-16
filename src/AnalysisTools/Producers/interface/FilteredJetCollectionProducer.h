#ifndef AnalysisTools_Producers_FilteredJetCollectionProducer
#define AnalysisTools_Producers_FilteredJetCollectionProducer

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "AnalysisTools/Producers/interface/FilteredCollectionProducer.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief FilteredJetCollectionProducer 
   * 
   * FilteredJetCollectionProducer
   ***********************************************/
  class FilteredJetCollectionProducer : public hepfw::FilteredCollectionProducer {
  public:
    
    FilteredJetCollectionProducer();
    FilteredJetCollectionProducer(std::string name);
    FilteredJetCollectionProducer(std::string name,hepfw::ParameterSet &pset);
    FilteredJetCollectionProducer(std::string name,std::string inputLabel,std::string outputLabel);
    ~FilteredJetCollectionProducer();
    
    
    void produce(hepfw::Event &event);
    
    void setMinPt      (double value);
    void setMaxEta     (double value);
    void doPFJetID     (bool   doIt);
    void doLoosePUIdMVA(bool   doIt);
    
  private:
    
    void init();
    bool calcPFJetID(ic::PFJet *jet);
    //bool calcPUIdMVALoose(hepfw::Event &event,ic::PFJet *jet);
    
  private:
    
    bool m_verbose;
    
    // Cut variables
    bool m_doMinPt;             double m_minPt;
    bool m_doMaxEta;            double m_maxEta;
    bool m_doPFJetID;
    bool m_doLoosePUIdMVA;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::FilteredJetCollectionProducer);
