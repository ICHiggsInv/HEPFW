#include "PostProcessing/Modules/interface/SequenceEventYields.h"

// HEPFW includes
#include "Latex/Table/interface/LatexTable.h"
#include "Latex/Table/interface/LatexTabular.h"
#include "Latex/Table/interface/LatexCaption.h"

// C++ STD includes
#include <utility>

using namespace std;

hepfw::SequenceEventYields::SequenceEventYields(){
  m_name="";
}

hepfw::SequenceEventYields::SequenceEventYields(std::string name){
  m_name = name;
}

hepfw::SequenceEventYields::SequenceEventYields(std::string name,hepfw::ParameterSet pset){
  m_name = name;
  
  m_processedData  = pset.getParameter<std::string>      ("processedData");
  m_histPath       = pset.getParameter<std::string>      ("path");
  m_outputFileName = pset.getParameter<std::string>      ("outputFileName");
  m_tableColumns   = pset.getParameterVector<std::string>("columns");
  m_commands       = pset.getParameterSet                ("commands");
}

hepfw::SequenceEventYields::~SequenceEventYields(){
  
}

void hepfw::SequenceEventYields::process(hepfw::ProcessedDataManager& data){
  
  vector<string> names;
  vector<TH1D*>  hYields;
  
  for(unsigned i=0; i<m_tableColumns.size(); i++){
    
    string tag = m_tableColumns[i];
    
    TH1D* h = (TH1D*) data.getTH1_byDataName_byDatasetTag(m_processedData,tag,m_histPath);
    
    names  .push_back(tag);
    hYields.push_back(h);
  }
  
  hepfw::LatexTable tblEvYields;
  tblEvYields.setCentering(true);
  tblEvYields.setPosition("htp");
//   tblEvYields.setLabel   (name);
  
  int nCuts = hYields[0]->GetNbinsX();
  
  hepfw::LatexTabular tabEvYields(nCuts+1,hYields.size()+1);
  tblEvYields.innerObjects.push_back(&tabEvYields);
  
  tabEvYields.setColumnAlignment(0,"l");
  tabEvYields.setTabularPrecision(".0");
  
  tabEvYields.setRowDecorationBefore(0,    "\\hline");
  tabEvYields.setRowDecorationBefore(1,    "\\hline \\hline");
  tabEvYields.setRowDecorationAfter (nCuts,"\\hline");
  
  for(unsigned i=0; i<hYields.size(); i++){
    tabEvYields.setCellContent(0,i+1,Form("\\rotatebox{90}{%s}",names[i].c_str()));
    tabEvYields.setColumnDecorationAfter(i,"|");
  }
  
  tabEvYields.setColumnDecorationBefore(0,"|");
  
  for(int i=1; i<=nCuts; i++){
    for(unsigned b=0; b<hYields.size(); b++){
      tabEvYields.setCellContent(i,0,Form("%s",hYields[0]->GetXaxis()->GetBinLabel(i)));
      tabEvYields.setCellContent(i,b+1,hYields[b]->GetBinContent(i));
    }
  }
  
  hepfw::LatexCaption capEvYields("Stuff");
  tblEvYields.innerObjects.push_back(&capEvYields);

  // Applying commands
  for(unsigned i=0; i<m_commands.size(); i++){
    
    // Getting this data
    hepfw::ParameterSet iCommand = m_commands.getParameterSet(i);
    string cmdName = iCommand.getParameter<std::string>("command");
    
    cout << "Command #" <<i<<" - "<<cmdName<<endl;
    
    if(cmdName=="FindAndReplace"){
      string strFind     = iCommand.getParameter<std::string>("find");    cout << "Find   : " << strFind << endl;
      string strRepalace = iCommand.getParameter<std::string>("replace"); cout << "Replace: " << strRepalace << endl;
      this->cmdFindAndReplace(tabEvYields,strFind,strRepalace);
    }
    
  }
  
  tblEvYields.saveAs(m_outputFileName.c_str());
  cout << "Output: " << m_outputFileName << endl;
}

/**
 * Implementation of command FindAndReplace over the tabular. This will search the cells of
 * an input tabular for a string given by input string find and replace it by input string 
 * replace.
 * @param tabular tabular to search for 
 * @param find string to find in all cells
 * @param replace string to replace all instances found
 ***********************************************/
void hepfw::SequenceEventYields::cmdFindAndReplace(hepfw::LatexTabular &tabular,std::string find,std::string replace){
  
  int nRow = tabular.getNRow();
  int nCol = tabular.getNColumn();

  //Checking all cells
  for(int iCol=0; iCol<nCol; iCol++){
    for(int iRow=0; iRow<nRow; iRow++){
      if(tabular.getCellContent(iRow,iCol)==find){
        tabular.setCellContent(iRow,iCol,replace);
      }
    }
  }
  
}
