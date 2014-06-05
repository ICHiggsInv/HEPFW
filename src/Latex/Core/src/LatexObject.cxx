#include "Latex/Core/interface/LatexObject.h"

#include <TString.h>

#include <stdio.h>
#include <iostream>

using namespace std;

void rat::LatexObject::print(){
  cout << this->toString() << endl;
}

std::string rat::LatexObject::toString(){
  return getRequiredPackagesString();
}

void rat::LatexObject::saveAs(string fileName){
  
  FILE * pFile;
  pFile = fopen (fileName.c_str(),"w");
  fprintf (pFile,"%s\n",this->toString().c_str());
  
}

void rat::LatexObject::addRequiredPackage(string packageName){
  m_requiredPackages.insert(packageName);
}

string rat::LatexObject::getRequiredPackagesString(){
  
  string out="";
  
  for(set<string>::iterator i=m_requiredPackages.begin(); i!=m_requiredPackages.end(); ++i){
    out += Form("\\usepackage{%s}\n",(*i).c_str());
  }
  
  return out;
}

set<string> rat::LatexObject::getRequiredPackages(){
  return m_requiredPackages;
}
  
