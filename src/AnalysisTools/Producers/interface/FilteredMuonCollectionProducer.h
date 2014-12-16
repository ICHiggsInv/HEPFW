#ifndef AnalysisTools_Producers_FilteredMuonCollectionProducer
#define AnalysisTools_Producers_FilteredMuonCollectionProducer

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "AnalysisTools/Producers/interface/FilteredCollectionProducer.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Muon.h"

// C++ STD includes
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief FilteredMuonCollectionProducer 
   * 
   * FilteredMuonCollectionProducer
   ***********************************************/
  class FilteredMuonCollectionProducer : public hepfw::FilteredCollectionProducer {
  public:
    
    FilteredMuonCollectionProducer();
    FilteredMuonCollectionProducer(std::string name);
    FilteredMuonCollectionProducer(std::string name,hepfw::ParameterSet &pset);
    FilteredMuonCollectionProducer(std::string name,std::string inputLabel,std::string outputLabel);
    ~FilteredMuonCollectionProducer();
    
    
    void produce(hepfw::Event &event);

    void setMinPt        (double value);
    void setMaxEta       (double value);
    void setMaxRelCombIso(double value); // Maximum relative combined isolation
    void setMaxDxy       (double value);
    void setMaxDz        (double value);
    void doMuonID_Tight  (bool   doIt);
    void setAllowedTypes (std::vector<std::string> values);
    void addAllowedType  (std::string value);
    
  private:
    
    void   init();
    double relativeCombinedIsolation_DR0p4(ic::Muon* mu);
    bool   isTightMuon                    (ic::Muon* mu); // As defined by CMS Muon POG for 2012/03 data (last review at 2014/12/11 at CMSPublic/SWGuideMuonId)
    
  private:

    bool m_verbose;
    
    // Cut variables
    bool m_doAllowedTypes;  std::vector<std::string> m_allowedTypes;
    bool m_doMinPt;         double m_minPt;
    bool m_doMaxEta;        double m_maxEta;
    bool m_doMaxRelCombIso; double m_maxRelCombIso;
    bool m_doMaxDxy;        double m_maxDxy;
    bool m_doMaxDz;         double m_maxDz;
    bool m_doMuonID_Tight;
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::FilteredMuonCollectionProducer);
