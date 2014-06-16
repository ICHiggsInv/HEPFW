#include "Algorithm/Mathmatics/interface/CombinationCalculator.h"

using namespace std;

/**********************************************************************************/
/** Default contructor
 **********************************************************************************/
rat::CombinationCalculator::CombinationCalculator(){
  m_nElements=0;
  m_nSelected=0;
}

/**********************************************************************************/
/** Constructor that takes as input the number of elements on the set and how many
 * elements are selected in each combination.
 * @param nElements number of elements on the set
 * @param nSelected number of selected elements on each combination
 **********************************************************************************/
rat::CombinationCalculator::CombinationCalculator(unsigned nElements,unsigned nSelected){
 
  m_nElements = nElements;
  m_nSelected = nSelected;
 
  // Setting initial combination
  m_currentCombination = vector<bool>(nElements);
  fill(m_currentCombination.begin() + m_nElements - m_nSelected, m_currentCombination.end(), true);
}

/**********************************************************************************/
/** Constructor that takes as input an initial combination
 * @param initialCombination initial combination where the iteration will start 
 **********************************************************************************/
rat::CombinationCalculator::CombinationCalculator(std::vector<bool> initialCombination){
  m_currentCombination = initialCombination;
  //TODO: set m_nSelected and m_nElements
}

/**********************************************************************************/
/** Set the number of elements on the set where calculations are to be calculated.
 * 
 * NOTE: The current combination will be reset when this method is called
 * @param nElements number of elements in the set
 **********************************************************************************/
void rat::CombinationCalculator::setNElements(unsigned nElements){
  
  m_nElements = nElements;
  
  // Setting initial combination
  m_currentCombination = vector<bool>(m_nElements);
  fill(m_currentCombination.begin() + m_nElements - m_nSelected, m_currentCombination.end(), true);
}

/**********************************************************************************/
/** Set the number of elements selected on each combination.
 * 
 * NOTE: The current combination will be reset when this method is called
 * @param nSelected number of elements selected on each combination
 **********************************************************************************/
void rat::CombinationCalculator::setNSelected(unsigned nSelected){
  
  m_nSelected = nSelected;
  
  // Setting initial combination
  m_currentCombination = vector<bool>(m_nElements);
  fill(m_currentCombination.begin() + m_nElements - m_nSelected, m_currentCombination.end(), true);
}

/**********************************************************************************/
/** Get number of elements on the set.
 * @return number of elements on the set
 **********************************************************************************/
unsigned rat::CombinationCalculator::getNElements(){
  return m_nElements;
}

/**********************************************************************************/
/** Get number of elements selected on each combination
 * @return number of elements selected on each combination
 **********************************************************************************/
unsigned rat::CombinationCalculator::getNSelected(){
  return m_nSelected;
}

/**********************************************************************************/
/** Get current combination
 * @return current combination
 **********************************************************************************/
std::vector<bool> rat::CombinationCalculator::getCombination(){
  return m_currentCombination;
}

/**********************************************************************************/
/** Iterate current combination to the next lexicographically greater combination
 * @return result of iteration, will be true except is this is the last combination.
 **********************************************************************************/
bool rat::CombinationCalculator::nextCombination(){
  return next_permutation(m_currentCombination.begin(), m_currentCombination.end());
}
