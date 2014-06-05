#ifndef ICTOOLS_PARAMETERS_PARAMETERSET
#define ICTOOLS_PARAMETERS_PARAMETERSET

// C++ Included
#include <string>
#include <vector>
#include <map>

namespace rat{
  
  /***********************************************/
  /** \brief ParameterSet
   * 
   * ParameterSet
   ***********************************************/
  class ParameterSet {
  public:
    
    void insertBool    (std::string key,bool value);
    void insertInt     (std::string key,int value);
    void insertFloat   (std::string key,float value);
    void insertDouble  (std::string key,double value);
    void insertString  (std::string key,std::string value);
    void insertVBool   (std::string key,std::vector<bool> value);
    void insertVInt    (std::string key,std::vector<int> value);
    void insertVFloat  (std::string key,std::vector<float> value);
    void insertVDouble (std::string key,std::vector<double> value);
    void insertVString (std::string key,std::vector<std::string> value);
    void insertMiBool  (std::string key,std::map<int,bool> value);
    void insertMiInt   (std::string key,std::map<int,int> value);
    void insertMiFloat (std::string key,std::map<int,float> value);
    void insertMiDouble(std::string key,std::map<int,double> value);
    void insertMiString(std::string key,std::map<int,std::string> value);
    void insertMsBool  (std::string key,std::map<std::string,bool> value);
    void insertMsInt   (std::string key,std::map<std::string,int> value);
    void insertMsFloat (std::string key,std::map<std::string,float> value);
    void insertMsDouble(std::string key,std::map<std::string,double> value);
    void insertMsString(std::string key,std::map<std::string,std::string> value);
    
    bool                              getBool    (std::string key);
    int                               getInt     (std::string key);
    float                             getFloat   (std::string key);
    double                            getDouble  (std::string key);
    std::string                       getString  (std::string key);
    std::vector<bool>                 getVBool   (std::string key);
    std::vector<int>                  getVInt    (std::string key);
    std::vector<float>                getVFloat  (std::string key);
    std::vector<double>               getVDouble (std::string key);
    std::vector<std::string>          getVString (std::string key);
    std::map<int,bool>                getMiBool  (std::string key);
    std::map<int,int>                 getMiInt   (std::string key);
    std::map<int,float>               getMiFloat (std::string key);
    std::map<int,double>              getMiDouble(std::string key);
    std::map<int,std::string>         getMiString(std::string key);
    std::map<std::string,bool>        getMsBool  (std::string key);
    std::map<std::string,int>         getMsInt   (std::string key);
    std::map<std::string,float>       getMsFloat (std::string key);
    std::map<std::string,double>      getMsDouble(std::string key);
    std::map<std::string,std::string> getMsString(std::string key);
    
    bool isSetBool    (std::string key);
    bool isSetInt     (std::string key);
    bool isSetFloat   (std::string key);
    bool isSetDouble  (std::string key);
    bool isSetString  (std::string key);
    bool isSetVBool   (std::string key);
    bool isSetVInt    (std::string key);
    bool isSetVFloat  (std::string key);
    bool isSetVDouble (std::string key);
    bool isSetVString (std::string key);
    bool isSetMiBool  (std::string key);
    bool isSetMiInt   (std::string key);
    bool isSetMiFloat (std::string key);
    bool isSetMiDouble(std::string key);
    bool isSetMiString(std::string key);
    bool isSetMsBool  (std::string key);
    bool isSetMsInt   (std::string key);
    bool isSetMsFloat (std::string key);
    bool isSetMsDouble(std::string key);
    bool isSetMsString(std::string key);
    
    std::string toString();
    
  private:
    
    // Maps for basics variables
    std::map<std::string,bool>        pBool_;
    std::map<std::string,int>         pInt_;
    std::map<std::string,float>       pFloat_;
    std::map<std::string,double>      pDouble_;
    std::map<std::string,std::string> pString_;
    
    // Maps for vectors of basics variables
    std::map<std::string,std::vector<bool> >        pVBool_;
    std::map<std::string,std::vector<int> >         pVInt_;
    std::map<std::string,std::vector<float> >       pVFloat_;
    std::map<std::string,std::vector<double> >      pVDouble_;
    std::map<std::string,std::vector<std::string> > pVString_;
    
    // Maps for maps (key string) of basics variables
    std::map<std::string,std::map<std::string,bool> >        pMsBool_;
    std::map<std::string,std::map<std::string,int> >         pMsInt_;
    std::map<std::string,std::map<std::string,float> >       pMsFloat_;
    std::map<std::string,std::map<std::string,double> >      pMsDouble_;
    std::map<std::string,std::map<std::string,std::string> > pMsString_;
    
    // Maps for maps (key int) of basics variables
    std::map<std::string,std::map<int,bool> >        pMiBool_;
    std::map<std::string,std::map<int,int> >         pMiInt_;
    std::map<std::string,std::map<int,float> >       pMiFloat_;
    std::map<std::string,std::map<int,double> >      pMiDouble_;
    std::map<std::string,std::map<int,std::string> > pMiString_;
    
  };
  
}

#endif
