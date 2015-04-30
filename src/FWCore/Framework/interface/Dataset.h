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
    
    void setCrossSection    (double xsec);
    void setNEventsProcessed(int nEvents);
    void setName            (std::string name);
    void setGroup           (std::string group);
    void setType            (std::string type);
    
    double      getCrossSection();
    int         getNEventsProcessed();
    std::string getName();
    std::string getGroup();
    std::string getType();
    
  private:
    
    std::string m_name;
    std::string m_group;
    std::string m_type;
    double      m_crossSection;
    //TODO: vector<hepfw::SampleWeight>
    
  };

}

#endif  
