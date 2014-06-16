// TODO: Description

// ICTools includes
#include "Algorithm/Mathmatics/interface/CombinationCalculator.h"

// Standard libraries includes
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

  rat::CombinationCalculator calc(8,3);
  
  do {
    vector<bool> combination = calc.getCombination();
    
    for (unsigned i=0; i<combination.size(); i++) {
      if(combination[i]){cout << "1";}
      else              {cout << "0";}
    }
    cout << "\n";
  } while (calc.nextCombination());
  
  return 0;
} 