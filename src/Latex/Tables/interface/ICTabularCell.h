#ifndef LATEX_TABLES_ICTABULARCELL
#define LATEX_TABLES_ICTABULARCELL

// C++ Included
#include <string>
#include <vector>

class ICTabularCell {
public:
  
  ICTabularCell();
  
  void set(std::string value);
  void set(bool        value);
  void set(int         value);
  void set(unsigned    value);
  void set(float       value);
  void set(double      value);
  
  std::string toString();
  
  
private:
  
  std::string m_cells;

};

#endif