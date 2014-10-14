#include "Latex/Core/interface/LatexObject.h"

#include <TString.h>

#include <stdio.h>
#include <iostream>

using namespace std;

void hepfw::LatexObject::print(){
  cout << this->toString() << endl;
}

std::string hepfw::LatexObject::toString(){
  return getRequiredPackagesString();
}

void hepfw::LatexObject::saveAs(string fileName){
  
  FILE * pFile;
  pFile = fopen (fileName.c_str(),"w");
  fprintf (pFile,"%s\n",this->toString().c_str());
  
}

void hepfw::LatexObject::addRequiredPackage(string packageName){
  m_requiredPackages.insert(packageName);
}

string hepfw::LatexObject::getRequiredPackagesString(){
  
  string out="";
  
  for(set<string>::iterator i=m_requiredPackages.begin(); i!=m_requiredPackages.end(); ++i){
    out += Form("\\usepackage{%s}\n",(*i).c_str());
  }
  
  return out;
}

set<string> hepfw::LatexObject::getRequiredPackages(){
  return m_requiredPackages;
}
  
