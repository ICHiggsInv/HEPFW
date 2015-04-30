#ifndef FWCORE_DATAFORMATS_DATATYPE
#define FWCORE_DATAFORMATS_DATATYPE

// C++ Included
#include <string>

namespace hepfw{
  
  enum VarType{
    kBool,
    kInt,
    kUnsigned,
    kFloat,
    kDouble,
    kString
  };
  
  /***********************************************/
  /** \brief DataType
   * 
   * DataType
   ***********************************************/   
  class DataType {
  public:
    
    DataType();
    
    VarType getType();
    
  protected:
    
    VarType m_varType;
    
  };
  
}

#endif