#ifndef ALGORITHM_MATHMATICS_COMBINATIONCALCULATOR
#define ALGORITHM_MATHMATICS_COMBINATIONCALCULATOR

// C++ Included
#include <string>
#include <vector>
#include <algorithm>

namespace rat{
  
  /**********************************************************************************/
  /** \brief A class to calculate all combination of a given set of elements
   * 
   * The CombinationCalculator class is able to generate all combinations of a
   * set of elements.
   * 
   * Assuming we want to get all combinations of X elements from a set of N elements,
   * this class will return a vector of N booleans where only the X of the elements
   * will be set to true. Every time the user calls method nextCombination() the 
   * current combination will be updated to the next value. 
   * 
   * This class makes use of the std library next_permutation() function, which will
   * iterate combinations by going into the next lexicographically greater permutation.
   * This means for the example of 5 elements and combinations of 2, the first 
   * combination will be {0,0,0,1,1} and the last one {1,1,0,0,0}.
   * 
   * This class can also be initialised to a specific initial combination allowing 
   * to run only over certain ranges of combination, which is specially useful if 
   * this code is being run several parallel jobs.
   **********************************************************************************/
  class CombinationCalculator{
  public:
    
    CombinationCalculator();
    CombinationCalculator(unsigned nElements,unsigned nSelected);    
    CombinationCalculator(std::vector<bool> initialCombination);
    
    void setNElements(unsigned nElements);
    void setNSelected(unsigned nSelected);
    
    unsigned          getNElements();
    unsigned          getNSelected();
    std::vector<bool> getCombination();
    
    bool nextCombination();
    
  private:
    
    unsigned          m_nElements;
    unsigned          m_nSelected;
    std::vector<bool> m_currentCombination;
    
  };
  
}

#endif