#ifndef AnalysisTools_CutFlows_VertexFilter
#define AnalysisTools_CutFlows_VertexFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <string>
#include <map>

namespace hepfw{
  
  /***********************************************/
  /** \brief HLT Path Filter
   * 
   * 
   ***********************************************/
  class VertexFilter : public hepfw::FilterModule {
  public:
    
    VertexFilter();
    VertexFilter(std::string name);
    VertexFilter(std::string name,hepfw::ParameterSet &pset);
    ~VertexFilter();
    
    bool filter(hepfw::Event &event);
    
  private:
    
    void init();

  private:
    
    bool m_verbose;
    
    std::string m_inputLabel;
    
    bool m_doMinNVertex;    unsigned m_minNVertex;
    bool m_doPV_minNTracks; unsigned m_pv_minNTracks;
    bool m_doPV_minChi2;    double   m_pv_minChi2;
    bool m_doPV_minNDof;    double   m_pv_minNDof;
    bool m_doPV_maxZ;       double   m_pv_maxZ;
    bool m_doPV_maxRho;     double   m_pv_maxRho;
    
  };
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::VertexFilter);
