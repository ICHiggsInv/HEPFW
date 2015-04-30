#ifndef AnalysisTools_Producers_FilteredTauCollectionProducer
#define AnalysisTools_Producers_FilteredTauCollectionProducer

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "AnalysisTools/Producers/interface/FilteredCollectionProducer.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Tau.h"

// C++ STD includes
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief FilteredTauCollectionProducer 
   * 
   * FilteredTauCollectionProducer
   ***********************************************/
  class FilteredTauCollectionProducer : public hepfw::FilteredCollectionProducer {
  public:
    
    FilteredTauCollectionProducer();
    FilteredTauCollectionProducer(std::string name);
    FilteredTauCollectionProducer(std::string name,hepfw::ParameterSet &pset);
    ~FilteredTauCollectionProducer();
    
    void produce(hepfw::Event &event);
    
    void setMinPt        (double value);
    void setMaxEta       (double value);
    void setMaxDxy       (double value);
    void setMaxDz        (double value);
    void setDescriminants(std::vector<std::string> values);
    
  private:
    
    void   init();
    
  private:
    
    bool m_verbose;
    
    // Cut variables
    bool m_doDiscriminants; std::vector<std::string> m_discriminants;
    bool m_doMinPt;         double m_minPt;
    bool m_doMaxEta;        double m_maxEta;
    bool m_doMaxDxy;        double m_maxDxy;
    bool m_doMaxDz;         double m_maxDz;
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::FilteredTauCollectionProducer);
