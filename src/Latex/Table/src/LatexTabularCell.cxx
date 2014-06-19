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
rat::LatexTabularCell::LatexTabularCell(){
  m_data = NULL;
}

rat::LatexTabularCell::LatexTabularCell(bool     value){m_data = new rat::Bool    (value);}
rat::LatexTabularCell::LatexTabularCell(int      value){m_data = new rat::Int     (value);}  
rat::LatexTabularCell::LatexTabularCell(unsigned value){m_data = new rat::Unsigned(value);}
rat::LatexTabularCell::LatexTabularCell(float    value){m_data = new rat::Float   (value);}
rat::LatexTabularCell::LatexTabularCell(double   value){m_data = new rat::Double  (value);}
rat::LatexTabularCell::LatexTabularCell(string   value){m_data = new rat::String  (value);}

rat::LatexTabularCell::~LatexTabularCell(){
  if(m_data!=NULL){delete m_data;}
}

void rat::LatexTabularCell::setCellContent(bool value){
  if(m_data!=NULL){delete m_data;}
  m_data = new rat::Bool(value);
}

void rat::LatexTabularCell::setCellContent(int value){
  if(m_data!=NULL){delete m_data;}
  m_data = new rat::Int(value);
}

void rat::LatexTabularCell::setCellContent(unsigned value){
  if(m_data!=NULL){delete m_data;}
  m_data = new rat::Unsigned(value);
}

void rat::LatexTabularCell::setCellContent(float value){
  if(m_data!=NULL){delete m_data;}
  m_data = new rat::Float(value);
}

void rat::LatexTabularCell::setCellContent(double value){
  if(m_data!=NULL){delete m_data;}
  m_data = new rat::Double(value);
}

void rat::LatexTabularCell::setCellContent(std::string value){
  if(m_data!=NULL){delete m_data;}
  m_data = new rat::String(value);
}

void rat::LatexTabularCell::setCellPrecision(std::string color){
  m_precision = color;  
}

std::string rat::LatexTabularCell::getCellPrecision(){
  return m_precision;
}


void rat::LatexTabularCell::setCellColor(std::string color){
  m_cellColor = color;  
}

std::string rat::LatexTabularCell::getCellColor(){
  return m_cellColor;
}

string rat::LatexTabularCell::toString(){

  string out="";

  if(m_data==NULL){return out;}
  
  if(m_data->getType() == kBool){
    rat::Bool* p = (rat::Bool*) m_data;
    if(p->get()){out = "1";}
    else        {out = "0";}
  }
  else if(m_data->getType() == kInt){
    rat::Int* p = (rat::Int*) m_data;
    string printString = Form("%%%si",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kUnsigned){
    rat::Unsigned* p = (rat::Unsigned*) m_data;
    string printString = Form("%%%si",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kFloat){
    rat::Float* p = (rat::Float*) m_data;
    string printString = Form("%%%sf",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kDouble){
    rat::Double* p = (rat::Double*) m_data;
    string printString = Form("%%%sf",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }  
  else if(m_data->getType() == kString){
    rat::String* p = (rat::String*) m_data;
    out = p->get();
  }
  
  return out;
  
}
