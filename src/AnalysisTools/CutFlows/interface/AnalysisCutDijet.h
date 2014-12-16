#ifndef AnalysisTools_CutFlows_AnalysisCutDijet
#define AnalysisTools_CutFlows_AnalysisCutDijet

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief AnalysisCutDijet 
   * 
   * AnalysisCutDijet
   ***********************************************/
  class AnalysisCutDijet : public hepfw::FilterModule {
  public:
    
    AnalysisCutDijet();
    AnalysisCutDijet(std::string name);
    AnalysisCutDijet(std::string name,hepfw::ParameterSet &pset);
    ~AnalysisCutDijet();
    
    bool filter(hepfw::Event &event);
    
    void setJetCollection(std::string jetsLabel);
    
    void setDijetFwdBck (bool fwdBck);
    void setDijetMinPt  (double jet0_pt,double jet1_pt);
    void setDijetEta    (double minEta,double maxEta);
    void setDijetMinDEta(double deta);
    void setDijetMinMjj (double mjj);
    
  private:
    
    void init();
    
  public:
    
    bool m_verbose;
    
    std::string m_jetsLabel;
    
    bool   m_fwdBck;
    double m_jet0_minPt;
    double m_jet1_minPt;
    double m_jet_minEta;
    double m_jet_maxEta;
    double m_dijet_minDEta;
    double m_dijet_minMjj;
    
  };

}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::AnalysisCutDijet);
