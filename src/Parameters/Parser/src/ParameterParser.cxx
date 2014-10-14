#include "Parameters/Parser/interface/ParameterParser.h"

#include "TString.h"

using namespace std;
using namespace boost;

hepfw::ParameterParser::ParameterParser(){}

hepfw::ParameterParser::ParameterParser(string fileName){

  m_fileName=fileName;  
  parse();

}

bool hepfw::ParameterParser::isPSetSet(std::string psetName){
  if(m_pSets.find(psetName)!=m_pSets.end()){return true;}
  else{return false;}
}

hepfw::ParameterSet hepfw::ParameterParser::getByName(std::string psetName){
  return m_pSets[psetName];
}

int hepfw::ParameterParser::getNPSet(){
  return m_pSets.size();
}

vector<string> hepfw::ParameterParser::removeComments(vector<string> words){

  vector<string> out;
  
  for(unsigned i=0; i<words.size(); i++){
    if((words[i])[0]!=string("#")){
      out.push_back(words[i]);
    }
    else{break;}
  }

  return out;
}

vector<string> hepfw::ParameterParser::removeEmpty(vector<string> words){

  vector<string> out;
  
  for(unsigned i=0; i<words.size(); i++){
    if((words[i])!=string("")){
      out.push_back(words[i]);
    }
  }
  
  return out;
}

void hepfw::ParameterParser::parse(){
/*
  ifstream infile;
  infile.open(m_fileName);

  int lineCount=0;
  
  cout << "Opening configuration file: "<<m_fileName<< endl;
  while (!infile.eof()){

    string sLine = "";
    getline(infile, sLine);
    trim(sLine);           // removing leading spaces
    lineCount++;
    
    if(sLine.size()==0) continue; // If empty line continue
    
    // Line is not empty, so we get all words
    vector<string> words;
    split(words, sLine, is_any_of(" "), token_compress_on );
    words = removeComments(words);
    words = removeEmpty(words);
  
    if(words.size()==0) continue; // If empty line or comment so continue

    // Dealing with wrong number if words
    if(words.size()!=3){
      printf("Malformed PSet initialization:%i Incorrect number of arguments (%i present, expected 3).\n",lineCount,words.size());
      return;
    } 
    
    // Dealing with missing PSet word 
    if(words[0]!=string("PSet")){
      printf("Malformed PSet initialization:%i Missing key word \"PSet\"\n.",lineCount);
      return;
    }

    // Getting pset information
    string psetType=words[1];
    string psetName=words[2];
    
    ICParameterSet pset;
    pset.insertString("type",psetType);
    pset.insertString("name",psetName);
    
    bool psetClosed = false; // Protecting from initialization of an improperly formatted pset
    
    while (sLine!="EndPSet" && !infile.eof()){
      getline(infile, sLine);
      trim(sLine);            // removing leading spaces
      lineCount++;
      
      vector<string> words;
      split(words, sLine, is_any_of(" "), token_compress_on );
      words = removeComments(words);
      words = removeEmpty(words);

      // If empty line or comment so continue
      if(words.size()==0) continue; 
      
      // If reached end of block continue
      if(words[0]=="EndPSet"){
        psetClosed=true;
        continue;
      }

      // Variable definition always has 3 fields, return if not
      if(words.size()!=3){
        printf("Malformed variable:%i Incorrect number of fields (%i present, expected 3).\n",lineCount,words.size());
	for(unsigned i=0; i<words.size(); i++){cout<<"word ["<<i<<"]: \""<<words[i]<<"\""<<endl;}
        return;
      }

      if(words[0]=="bool"){
        int  parse = TString(words[2]).Atoi();
        bool value = false;
        if(parse==1){value=true;}
        pset.insertBool(words[1],value);
      }
      else if(words[0]=="int"){
        int value = TString(words[2]).Atoi();
        pset.insertInt(words[1],value);
      }
      else if(words[0]=="float"){
        float value = TString(words[2]).Atof();
        pset.insertFloat(words[1],value);
      }
      else if(words[0]=="double"){
        double value = TString(words[2]).Atof();
        pset.insertDouble(words[1],value);
      }
      else if(words[0]=="string"){
        pset.insertString(words[1],words[2]);
      }
      else if(words[0]=="vbool"){
        vector<bool> value;
        vector<string> vValues;
        split( vValues, words[2], is_any_of(","), token_compress_on );
        for(unsigned i=0; i<vValues.size(); i++){
          int parse = TString(vValues[i]).Atoi();
          if(parse==0){value.push_back(false);}
          else        {value.push_back(true);}
        }
        pset.insertVBool(words[1],value);
      }
      else if(words[0]=="vint"){
        vector<int> value;
        vector<string> vValues;
        split( vValues, words[2], is_any_of(","), token_compress_on );
        for(unsigned i=0; i<vValues.size(); i++){
          value.push_back(TString(vValues[i]).Atoi());
        }
        pset.insertVInt(words[1],value);
      }
      else if(words[0]=="vfloat"){
        vector<float> value;
        vector<string> vValues;
        split( vValues, words[2], is_any_of(","), token_compress_on );
        for(unsigned i=0; i<vValues.size(); i++){
          value.push_back(TString(vValues[i]).Atof());
        }
        pset.insertVFloat(words[1],value);
      }
      else if(words[0]=="vdouble"){
        vector<double> value;
        vector<string> vValues;
        split( vValues, words[2], is_any_of(","), token_compress_on );
        for(unsigned i=0; i<vValues.size(); i++){
          value.push_back(TString(vValues[i]).Atof());
        }
        pset.insertVDouble(words[1],value);
      }
      else if(words[0]=="vstring"){
        vector<string> value;
        vector<string> vValues;
        split( vValues, words[2], is_any_of(","), token_compress_on );
        for(unsigned i=0; i<vValues.size(); i++){
          value.push_back(vValues[i]);
        }
        pset.insertVString(words[1],value);
      }
    }
    if(!psetClosed && infile.eof()){
	printf("Pset not closed: reached end of file without finding \"EndBlock\" statement.");
      return;
    }
    else{
	m_pSets[psetName]=pset;
    }
  }
  infile.close();
  cout << "Close configuration file" << endl;*/
  
}
