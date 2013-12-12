#include "Latex/Tables/interface/ICTableCaption.h"

#include "TString.h"

using namespace std;

ICTableCaption::ICTableCaption(){}

ICTableCaption::ICTableCaption(const char* value){
  m_caption = string(value);
}

void ICTableCaption::set(string value){m_caption=value;}
  
string ICTableCaption::get(){return m_caption;}

string ICTableCaption::toString(){return Form("\\caption{%s}\n",m_caption.c_str());}