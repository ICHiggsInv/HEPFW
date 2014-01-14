#include "Latex/Table/interface/ICLatexCaption.h"

#include "TString.h"

using namespace std;

ICLatexCaption::ICLatexCaption(){}

ICLatexCaption::ICLatexCaption(const char* value){
  m_caption = string(value);
}

void ICLatexCaption::set(string value){m_caption=value;}
  
string ICLatexCaption::get(){return m_caption;}

string ICLatexCaption::toString(){return Form("\\caption{%s}\n",m_caption.c_str());}