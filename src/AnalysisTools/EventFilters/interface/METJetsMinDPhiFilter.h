#ifndef AnalysisTools_CutFlows_METJetsMinDPhiFilter
#define AnalysisTools_CutFlows_METJetsMinDPhiFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"

// C++ STD includes
#include <string>
#include <map>
#include <functional>

namespace hepfw{
  
  /***********************************************/
  /** \brief HLT Path Filter
   * 
   * 
   ***********************************************/
  class METJetsMinDPhiFilter : public hepfw::FilterModule {
  public:
    
    METJetsMinDPhiFilter();
    METJetsMinDPhiFilter(std::string name);
    METJetsMinDPhiFilter(std::string name,hepfw::ParameterSet &pset);
    ~METJetsMinDPhiFilter();
    
    bool filter(hepfw::Event &event);
    
    void setJetCollection  (std::string jetsLabel);
    void setMetCollection  (std::string metLabel);

    void setMinJetPt       (double      minPt);
    void setMinDPhi        (double      minDPhi);
    void setOperatorMinDPhi(std::string value);
    
  private:
    
    void init();
    
    bool test_DPhi_BiggerThan(double &metPhi,double &jetPhi,double &value);
    bool test_DPhi_LessThan  (double &metPhi,double &jetPhi,double &value);
    
  private:
    
    std::function<bool (hepfw::METJetsMinDPhiFilter*,double &metPhi,double &jetPhi,double &value)> testFunc;
    
    bool m_verbose;
    
    std::string m_metLabel;
    std::string m_jetsLabel;
    double      m_minJetPt;
    
    std::string m_op_minDPhi;
    double      m_minDPhi;
    
  };
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::METJetsMinDPhiFilter);
