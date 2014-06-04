#include "Latex/Table/interface/ICLatexCaption.h"

#include "TString.h"

using namespace std;

/***********************************************/
/** Default constructor
 ***********************************************/
ICLatexCaption::ICLatexCaption(){}

/***********************************************/
/** Constructor that will take the text of the caption as input
 * \param value text for this caption
 ***********************************************/
ICLatexCaption::ICLatexCaption(const char* value){
  m_caption = string(value);
}

/***********************************************/
/** Sets text for this caption
 * \param value text for this caption
 ***********************************************/
void ICLatexCaption::set(string value){m_caption=value;}

/***********************************************/
/** Gets text of this caption
 * \return text of this caption
 ***********************************************/
string ICLatexCaption::get(){return m_caption;}

/***********************************************/
/** Converts and returns contents in std::string format
 * \return contents in string format
 ***********************************************/
string ICLatexCaption::toString(){return Form("\\caption{%s}\n",m_caption.c_str());}