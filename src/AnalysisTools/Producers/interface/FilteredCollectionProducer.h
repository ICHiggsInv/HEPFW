#ifndef AnalysisTools_Producers_FilteredCollectionProducer
#define AnalysisTools_Producers_FilteredCollectionProducer

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/ProducerModule.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief FilteredCollectionProducer 
   * 
   * FilteredCollectionProducer
   ***********************************************/
  class FilteredCollectionProducer : public hepfw::ProducerModule {
  public:
    
    FilteredCollectionProducer();
    FilteredCollectionProducer(std::string name);
    FilteredCollectionProducer(std::string name,std::string inputLabel,std::string outputLabel);
    ~FilteredCollectionProducer();
    
   virtual void produce(hepfw::Event &event);
    
    void setInputLabel (std::string inputLabel);
    void setOutputLabel(std::string outputLabel);
    
  protected:

    std::string m_inputLabel;
    std::string m_outputLabel;

  };
}

#endif
