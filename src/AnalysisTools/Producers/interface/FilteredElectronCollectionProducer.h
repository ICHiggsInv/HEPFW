#ifndef AnalysisTools_Producers_FilteredElectronCollectionProducer
#define AnalysisTools_Producers_FilteredElectronCollectionProducer

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "AnalysisTools/Producers/interface/FilteredCollectionProducer.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Electron.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief FilteredElectronCollectionProducer 
   * 
   * FilteredElectronCollectionProducer
   ***********************************************/
  class FilteredElectronCollectionProducer : public hepfw::FilteredCollectionProducer {
  public:
    
    FilteredElectronCollectionProducer();
    FilteredElectronCollectionProducer(std::string name);
    FilteredElectronCollectionProducer(std::string name,hepfw::ParameterSet &pset);
    FilteredElectronCollectionProducer(std::string name,std::string inputLabel,std::string outputLabel);
    ~FilteredElectronCollectionProducer();
    
    void produce(hepfw::Event &event);

    void setMinPt                   (double value);
    void setMaxEta                  (double value);
    void setMaxEffAreaCorrIso       (double value); // Maximum effective area corrected isolation
    void setMaxDxy                  (double value);
    void setMaxDz                   (double value);
    void doElectronID_CutBased_Veto (bool   doIt);
    void doElectronID_CutBased_Tight(bool   doIt);
    
  private:

    void   init();
    double calcEffAreaCorrIso(hepfw::Event &event,ic::Electron *el);
    
  private:
    
    bool m_verbose;
    
    // Cut variables
    bool m_doMinPt;             double m_minPt;
    bool m_doMaxEta;            double m_maxEta;
    bool m_doMaxEffAreaCorrIso; double m_maxEffAreaCorrIso;
    bool m_doMaxDxy;            double m_maxDxy;
    bool m_doMaxDz;             double m_maxDz;
    bool m_doElectronID_CutBased_Veto;
    bool m_doElectronID_CutBased_Tight;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::FilteredElectronCollectionProducer);
