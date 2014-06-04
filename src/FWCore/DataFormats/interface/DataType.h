#ifndef FWCORE_DATAFORMATS_ICDATATYPE
#define FWCORE_DATAFORMATS_ICDATATYPE

// C++ Included
#include <string>

enum VarType{
  kBool,
  kInt,
  kUnsigned,
  kFloat,
  kDouble,
  kString
};


class ICDataType {
public:

  ICDataType();

  VarType getType();
  
protected:

  VarType m_varType;
  
};

#endif