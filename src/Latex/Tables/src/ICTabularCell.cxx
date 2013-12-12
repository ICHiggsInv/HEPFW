#include "Latex/Tables/interface/ICTabularCell.h"

#include "FWCore/DataFormats/interface/ICBool.h"
#include "FWCore/DataFormats/interface/ICInt.h"
#include "FWCore/DataFormats/interface/ICUnsigned.h"
#include "FWCore/DataFormats/interface/ICFloat.h"
#include "FWCore/DataFormats/interface/ICDouble.h"
#include "FWCore/DataFormats/interface/ICString.h"

#include "TString.h"
#include <iostream>

using namespace std;

ICTabularCell::ICTabularCell(){
  m_data = NULL;
}

ICTabularCell::ICTabularCell(bool        value){m_data = new ICBool    (value);}
ICTabularCell::ICTabularCell(int         value){m_data = new ICInt     (value);}  
ICTabularCell::ICTabularCell(unsigned    value){m_data = new ICUnsigned(value);}
ICTabularCell::ICTabularCell(float       value){m_data = new ICFloat   (value);}
ICTabularCell::ICTabularCell(double      value){m_data = new ICDouble  (value);}
ICTabularCell::ICTabularCell(std::string value){m_data = new ICString  (value);}

ICTabularCell::~ICTabularCell(){
  if(m_data==NULL){delete m_data;}
}

void ICTabularCell::set(bool value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICBool(value);
}

void ICTabularCell::set(int value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICInt(value);
}

void ICTabularCell::set(unsigned value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICUnsigned(value);
}

void ICTabularCell::set(float value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICFloat(value);
}

void ICTabularCell::set(double value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICDouble(value);
}

void ICTabularCell::set(std::string value){
  if(m_data==NULL){delete m_data;}
  m_data = new ICString(value);
}

string ICTabularCell::toString(){
  cout << m_data->getType() << endl;
  if     (m_data->getType() == kBool){
    ICBool* p = (ICBool*) m_data;
    if(p->get()){return "1";}
    else        {return "0";}
  }
  else if(m_data->getType() == kInt){
    ICInt* p = (ICInt*) m_data;
    return Form("%i",p->get());
  }
  else if(m_data->getType() == kUnsigned){
    ICUnsigned* p = (ICUnsigned*) m_data;
    return Form("%i",p->get());    
  }
  else if(m_data->getType() == kFloat){
    ICFloat* p = (ICFloat*) m_data;
    return Form("%f",p->get());
  }
  else if(m_data->getType() == kDouble){
    ICDouble* p = (ICDouble*) m_data;
    return Form("%f",p->get());
  }  
  else if(m_data->getType() == kString){
    ICString* p = (ICString*) m_data;
    return p->get();
  }
  
}