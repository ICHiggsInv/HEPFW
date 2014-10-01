#include "Latex/Table/interface/LatexTabularCell.h"

#include "FWCore/DataFormats/interface/Bool.h"
#include "FWCore/DataFormats/interface/Int.h"
#include "FWCore/DataFormats/interface/Unsigned.h"
#include "FWCore/DataFormats/interface/Float.h"
#include "FWCore/DataFormats/interface/Double.h"
#include "FWCore/DataFormats/interface/String.h"

#include "TString.h"
#include <iostream>

using namespace std;

/***********************************************/
/** Default constructor
 ***********************************************/
hepfw::LatexTabularCell::LatexTabularCell(){
  m_data = NULL;
}

hepfw::LatexTabularCell::~LatexTabularCell(){
  if(m_data!=NULL){delete m_data;}
}

hepfw::LatexTabularCell::LatexTabularCell(bool     value){m_data = new hepfw::Bool    (value);}
hepfw::LatexTabularCell::LatexTabularCell(int      value){m_data = new hepfw::Int     (value);}  
hepfw::LatexTabularCell::LatexTabularCell(unsigned value){m_data = new hepfw::Unsigned(value);}
hepfw::LatexTabularCell::LatexTabularCell(float    value){m_data = new hepfw::Float   (value);}
hepfw::LatexTabularCell::LatexTabularCell(double   value){m_data = new hepfw::Double  (value);}
hepfw::LatexTabularCell::LatexTabularCell(string   value){m_data = new hepfw::String  (value);}

void hepfw::LatexTabularCell::setCellContent(bool value){
  if(m_data!=NULL){delete m_data;}
  m_data = new hepfw::Bool(value);
}

void hepfw::LatexTabularCell::setCellContent(int value){
  if(m_data!=NULL){delete m_data;}
  m_data = new hepfw::Int(value);
}

void hepfw::LatexTabularCell::setCellContent(unsigned value){
  if(m_data!=NULL){delete m_data;}
  m_data = new hepfw::Unsigned(value);
}

void hepfw::LatexTabularCell::setCellContent(float value){
  if(m_data!=NULL){delete m_data;}
  m_data = new hepfw::Float(value);
}

void hepfw::LatexTabularCell::setCellContent(double value){
  if(m_data!=NULL){delete m_data;}
  m_data = new hepfw::Double(value);
}

void hepfw::LatexTabularCell::setCellContent(std::string value){
  if(m_data!=NULL){delete m_data;}
  m_data = new hepfw::String(value);
}

void hepfw::LatexTabularCell::setCellPrecision(std::string color){
  m_precision = color;  
}

std::string hepfw::LatexTabularCell::getCellPrecision(){
  return m_precision;
}


void hepfw::LatexTabularCell::setCellColor(std::string color){
  m_cellColor = color;  
}

std::string hepfw::LatexTabularCell::getCellColor(){
  return m_cellColor;
}

string hepfw::LatexTabularCell::toString(){

  string out="";

  if(m_data==NULL){return out;}
  
  if(m_data->getType() == kBool){
    hepfw::Bool* p = (hepfw::Bool*) m_data;
    if(p->get()){out = "1";}
    else        {out = "0";}
  }
  else if(m_data->getType() == kInt){
    hepfw::Int* p = (hepfw::Int*) m_data;
    string printString = Form("%%%si",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kUnsigned){
    hepfw::Unsigned* p = (hepfw::Unsigned*) m_data;
    string printString = Form("%%%si",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kFloat){
    hepfw::Float* p = (hepfw::Float*) m_data;
    string printString = Form("%%%sf",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kDouble){
    hepfw::Double* p = (hepfw::Double*) m_data;
    string printString = Form("%%%sf",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }  
  else if(m_data->getType() == kString){
    hepfw::String* p = (hepfw::String*) m_data;
    out = p->get();
  }
  
  return out;
  
}
