#ifndef FWCore_Framework_Event
#define FWCore_Framework_Event

// HEPFW includes
#include "FWCore/Framework/interface/Dataset.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief Event
   * 
   * Event
   ***********************************************/
  class Event {
  public:
    
    Event();
    ~Event();
    
  private:
    
    hepfw::Dataset* m_dataset;
    
  };

}

#endif 