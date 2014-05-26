#include "Latex/Table/interface/ICLatexTabularCell.h"

#include "FWCore/DataFormats/interface/ICBool.h"
#include "FWCore/DataFormats/interface/ICInt.h"
#include "FWCore/DataFormats/interface/ICUnsigned.h"
#include "FWCore/DataFormats/interface/ICFloat.h"
#include "FWCore/DataFormats/interface/ICDouble.h"
#include "FWCore/DataFormats/interface/ICString.h"

#include "TString.h"
#include <iostream>

using namespace std;

/***********************************************/
/** Default constructor
 ***********************************************/
ICLatexTabularCell::ICLatexTabularCell(){
  m_data = NULL;
}

ICLatexTabularCell::ICLatexTabularCell(bool     value){m_data = new ICBool    (value);}
ICLatexTabularCell::ICLatexTabularCell(int      value){m_data = new ICInt     (value);}  
ICLatexTabularCell::ICLatexTabularCell(unsigned value){m_data = new ICUnsigned(value);}
ICLatexTabularCell::ICLatexTabularCell(float    value){m_data = new ICFloat   (value);}
ICLatexTabularCell::ICLatexTabularCell(double   value){m_data = new ICDouble  (value);}
ICLatexTabularCell::ICLatexTabularCell(string   value){m_data = new ICString  (value);}

ICLatexTabularCell::~ICLatexTabularCell(){
  if(m_data!=NULL){delete m_data;}
}

void ICLatexTabularCell::setCellContent(bool value){
  if(m_data!=NULL){delete m_data;}
  m_data = new ICBool(value);
}

void ICLatexTabularCell::setCellContent(int value){
  if(m_data!=NULL){delete m_data;}
  m_data = new ICInt(value);
}

void ICLatexTabularCell::setCellContent(unsigned value){
  if(m_data!=NULL){delete m_data;}
  m_data = new ICUnsigned(value);
}

void ICLatexTabularCell::setCellContent(float value){
  if(m_data!=NULL){delete m_data;}
  m_data = new ICFloat(value);
}

void ICLatexTabularCell::setCellContent(double value){
  if(m_data!=NULL){delete m_data;}
  m_data = new ICDouble(value);
}

void ICLatexTabularCell::setCellContent(std::string value){
  if(m_data!=NULL){delete m_data;}
  m_data = new ICString(value);
}

void ICLatexTabularCell::setCellPrecision(std::string color){
  m_precision = color;  
}

std::string ICLatexTabularCell::getCellPrecision(){
  return m_precision;
}


void ICLatexTabularCell::setCellColor(std::string color){
  m_cellColor = color;  
}

std::string ICLatexTabularCell::getCellColor(){
  return m_cellColor;
}

string ICLatexTabularCell::toString(){

  string out="";

  if(m_data==NULL){return out;}
  
  if(m_data->getType() == kBool){
    ICBool* p = (ICBool*) m_data;
    if(p->get()){out = "1";}
    else        {out = "0";}
  }
  else if(m_data->getType() == kInt){
    ICInt* p = (ICInt*) m_data;
    string printString = Form("%%%si",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kUnsigned){
    ICUnsigned* p = (ICUnsigned*) m_data;
    string printString = Form("%%%si",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kFloat){
    ICFloat* p = (ICFloat*) m_data;
    string printString = Form("%%%sf",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }
  else if(m_data->getType() == kDouble){
    ICDouble* p = (ICDouble*) m_data;
    string printString = Form("%%%sf",m_precision.c_str());
    out = Form(printString.c_str(),p->get());
  }  
  else if(m_data->getType() == kString){
    ICString* p = (ICString*) m_data;
    out = p->get();
  }
  
  return out;
  
}
