#ifndef FWCore_Framework_Dataset
#define FWCore_Framework_Dataset

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief Dataset
   * 
   * Dataset
   ***********************************************/
  class Dataset {
  public:
    
    Dataset();
    ~Dataset();
    
  private:
    
    std::string m_name;
    std::string m_group;
    std::string m_type;
    double      m_crossSection;
    //TODO: vector<hepfw::SampleWeight>
    
  };

}

#endif  
