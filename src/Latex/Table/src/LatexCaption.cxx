#include "Latex/Table/interface/LatexCaption.h"

#include "TString.h"

using namespace std;

/***********************************************/
/** Default constructor
 ***********************************************/
hepfw::LatexCaption::LatexCaption(){}

/***********************************************/
/** Constructor that will take the text of the caption as input
 * \param value text for this caption
 ***********************************************/
hepfw::LatexCaption::LatexCaption(const char* value){
  m_caption = string(value);
}

/***********************************************/
/** Sets text for this caption
 * \param value text for this caption
 ***********************************************/
void hepfw::LatexCaption::set(string value){m_caption=value;}

/***********************************************/
/** Gets text of this caption
 * \return text of this caption
 ***********************************************/
string hepfw::LatexCaption::get(){return m_caption;}

/***********************************************/
/** Converts and returns contents in std::string format
 * \return contents in string format
 ***********************************************/
string hepfw::LatexCaption::toString(){return Form("\\caption{%s}\n",m_caption.c_str());}