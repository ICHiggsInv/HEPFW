#ifndef ICTOOLS_PARAMETERS_ICPARAMETERPARSER
#define ICTOOLS_PARAMETERS_ICPARAMETERPARSER

#include "Parameters/Parser/interface/ICParameterSet.h"

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

class ICParameterParser {
public:
  ICParameterParser();
  ICParameterParser(std::string fileName);

  bool           isPSetSet(std::string psetName);
  ICParameterSet getByName(std::string psetName);
  int            getNPSet();  
  
private:  
  std::vector<std::string> removeComments(std::vector<std::string> words);
  std::vector<std::string> removeEmpty   (std::vector<std::string> words);
  void                     parse();

private:

  std::string m_fileName;
  std::map<std::string,ICParameterSet> m_pSets;
  
};

#endif
