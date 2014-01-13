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

ICLatexTabularCell::ICLatexTabularCell(){
  m_data = NULL;
}

ICLatexTabularCell::ICLatexTabularCell(bool        value){m_data = new ICBool    (value);}
ICLatexTabularCell::ICLatexTabularCell(int         value){m_data = new ICInt     (value);}  
ICLatexTabularCell::ICLatexTabularCell(unsigned    value){m_data = new ICUnsigned(value);}
ICLatexTabularCell::ICLatexTabularCell(float       value){m_data = new ICFloat   (value);}
ICLatexTabularCell::ICLatexTabularCell(double      value){m_data = new ICDouble  (value);}
ICLatexTabularCell::ICLatexTabularCell(std::string value){m_data = new ICString  (value);}

ICLatexTabularCell::~ICLatexTabularCell(){
  if(m_data==NULL){delete m_data;}
}

void ICLatexTabularCell::set(bool value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICBool(value);
}

void ICLatexTabularCell::set(int value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICInt(value);
}

void ICLatexTabularCell::set(unsigned value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICUnsigned(value);
}

void ICLatexTabularCell::set(float value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICFloat(value);
}

void ICLatexTabularCell::set(double value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICDouble(value);
}

void ICLatexTabularCell::set(std::string value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICString(value);
}

string ICLatexTabularCell::toString(){

  string out="";
  
  if     (m_data->getType() == kBool){
    ICBool* p = (ICBool*) m_data;
    if(p->get()){out = "1";}
    else        {out = "0";}
  }
  else if(m_data->getType() == kInt){
    ICInt* p = (ICInt*) m_data;
    out = Form("%i",p->get());
  }
  else if(m_data->getType() == kUnsigned){
    ICUnsigned* p = (ICUnsigned*) m_data;
    out = Form("%i",p->get());    
  }
  else if(m_data->getType() == kFloat){
    ICFloat* p = (ICFloat*) m_data;
    out = Form("%f",p->get());
  }
  else if(m_data->getType() == kDouble){
    ICDouble* p = (ICDouble*) m_data;
    out = Form("%f",p->get());
  }  
  else if(m_data->getType() == kString){
    ICString* p = (ICString*) m_data;
    out = p->get();
  }
  
  return out;
  
}
