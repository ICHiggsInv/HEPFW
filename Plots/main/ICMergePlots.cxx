// TODO: Description

#include "TFile.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
  
  if(argc<3){
    printf("usage: %s <OutputFile> <InputFile0> (...)\n", argv[0]); 
    return 0;
  }
  
  printf("Output file: %s\n", argv[1]);
  for(int i=2; i<argc; i++){
    printf("Input file: %s\n", argv[i]);
  }
  
  return 0;
  
}