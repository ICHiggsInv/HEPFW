#ifndef ICTOOLS_PARAMETERS_PARAMETERPARSER
#define ICTOOLS_PARAMETERS_PARAMETERPARSER

#include "Parameters/Parser/interface/ParameterSet.h"

// C++ Included
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <sys/stat.h>

namespace rat{
  
  /***********************************************/
  /** \brief ParameterParser
   * 
   * ParameterParser
   ***********************************************/
  class ParameterParser {
  public:
    ParameterParser();
    ParameterParser(std::string fileName);
    
    bool         isPSetSet(std::string psetName);
    ParameterSet getByName(std::string psetName);
    int          getNPSet();  
    
  private:  
    std::vector<std::string> removeComments(std::vector<std::string> words);
    std::vector<std::string> removeEmpty   (std::vector<std::string> words);
    void                     parse();
    
  private:
    
    std::string                          m_fileName;
    std::map<std::string,rat::ParameterSet> m_pSets;
    
  };
  
}

#endif
