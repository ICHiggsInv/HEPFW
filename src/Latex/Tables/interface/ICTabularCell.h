#ifndef LATEX_TABLES_ICTABULARCELL
#define LATEX_TABLES_ICTABULARCELL

// C++ Included
#include <string>
#include <vector>

class ICTabularCell {
public:
  
  void set(std::string value);
  std::string toString();
  
  
private:

  std::string m_cells;

};

#endif