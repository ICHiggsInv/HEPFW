#include "Latex/Tables/interface/ICTabularCell.h"

using namespace std;

ICTabularCell::ICTabularCell(){
  
  cellType = kString;

  
}
  
void ICTabularCell::set(std::string value){
  cellType = kString;
  m_cells  = value; 
}

void ICTabularCell::set(bool value){
  cellType = kBool;
  m_cells  = value;   
}

void ICTabularCell::set(int value){
  cellType = kInt;
  m_cells  = value; 
}

void ICTabularCell::set(unsigned value){
  cellType = kUnsigned;
  m_cells  = value; 
}

void ICTabularCell::set(float value){
  cellType = kFloat;
  m_cells  = value; 
}

void ICTabularCell::set(double value){
  cellType = kDouble;
  m_cells  = value; 
}

string ICTabularCell::toString(){
 
  string out;
  
  if(cellType == kString){return m_cells;}
  
  
  
}