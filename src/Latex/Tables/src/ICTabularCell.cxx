#include "Latex/Tables/interface/ICTabularCell.h"

using namespace std;

ICTabularCell::ICTabularCell(){}
  
void ICTabularCell::set(std::string value){m_cells  = value;}

string ICTabularCell::toString(){return m_cells;}