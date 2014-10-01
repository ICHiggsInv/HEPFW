// TODO: Description

// ICTools includes
#include "Algorithm/Mathmatics/interface/CombinationCalculator.h"

// Standard libraries includes
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

  cout << "Now calculating all combinations of 3 out of 8 elements:" << endl;
  hepfw::CombinationCalculator calc1(8,3);
  
  do {
    vector<bool> combination = calc1.getCombination();
    
    for (unsigned i=0; i<combination.size(); i++) {
      if(combination[i]){cout << "1";}
      else              {cout << "0";}
    }
    cout << "\n";
  } while (calc1.nextCombination());
  
  //____________________________________________________________________________
  cout << "Now calculating all combinations of 3 out of 5 elements but stating at combination (01010):" << endl;
  
  vector<bool> initialValue(5);
  initialValue[1] = 1;
  initialValue[3] = 1;
  
  hepfw::CombinationCalculator calc2(initialValue);  
  do {
    vector<bool> combination = calc2.getCombination();
    
    for (unsigned i=0; i<combination.size(); i++) {
      if(combination[i]){cout << "1";}
      else              {cout << "0";}
    }
    cout << "\n";
  } while (calc2.nextCombination());  
  
  return 0;
} 