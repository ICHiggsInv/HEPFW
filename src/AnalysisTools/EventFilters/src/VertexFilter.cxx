#include "AnalysisTools/EventFilters/interface/VertexFilter.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Vertex.h"

// C++ STD includes
#include <vector>
#include <iostream>

using namespace std;

hepfw::VertexFilter::VertexFilter(){
  
  // Setting default values;
  this->init();
  m_name = "";
}

hepfw::VertexFilter::VertexFilter(string name){
  
  // Setting default values;
  m_name = name;
  this->init();
}

hepfw::VertexFilter::~VertexFilter(){
  
}

hepfw::VertexFilter::VertexFilter(std::string name,hepfw::ParameterSet &pset){

  // Setting default values;
  this->init();
  
  m_name       = name;
  m_inputLabel = pset.getParameter<string>("inputLabel");
  
  if(pset.isParameterDefined("verbose"      )){m_verbose = pset.getParameter<bool>("verbose");}
  if(pset.isParameterDefined("minNVertex"   )){m_doMinNVertex    = true; m_minNVertex    = pset.getParameter<unsigned>("minNVertex"   );}
  if(pset.isParameterDefined("pv_minNTracks")){m_doPV_minNTracks = true; m_pv_minNTracks = pset.getParameter<unsigned>("pv_minNTracks");}
  if(pset.isParameterDefined("pv_minChi2"   )){m_doPV_minChi2    = true; m_pv_minChi2    = pset.getParameter<double>  ("pv_minChi2"   );}
  if(pset.isParameterDefined("pv_minNDof"   )){m_doPV_minNDof    = true; m_pv_minNDof    = pset.getParameter<double>  ("pv_minNDof"   );}
  if(pset.isParameterDefined("pv_maxZ"      )){m_doPV_maxZ       = true; m_pv_maxZ       = pset.getParameter<double>  ("pv_maxZ"      );}
  if(pset.isParameterDefined("pv_maxRho"    )){m_doPV_maxRho     = true; m_pv_maxRho     = pset.getParameter<double>  ("pv_maxRho"    );}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::VertexFilter\n");
    printf("InputLabel        : %s\n",m_inputLabel.c_str());
    if(m_doMinNVertex   ) {printf("minNVertex    : %d\n",  m_minNVertex   );}
    if(m_doPV_minNTracks) {printf("pv_minNTracks : %d\n",  m_pv_minNTracks);}
    if(m_doPV_minChi2   ) {printf("pv_minChi2    : %.2f\n",m_pv_minChi2   );}
    if(m_doPV_minNDof   ) {printf("pv_minNDof    : %.2f\n",m_pv_minNDof   );}
    if(m_doPV_maxZ      ) {printf("pv_maxZ       : %.2f\n",m_pv_maxZ      );}
    if(m_doPV_maxRho    ) {printf("pv_maxRho     : %.2f\n",m_pv_maxRho    );}
  }
}

void hepfw::VertexFilter::init(){
  
  m_verbose    = false;
  m_inputLabel = "";
  
  m_doMinNVertex    = false;
  m_doPV_minNTracks = false;
  m_doPV_minChi2    = false;
  m_doPV_minNDof    = false;
  m_doPV_maxZ       = false;
  m_doPV_maxRho     = false;
  
}

bool hepfw::VertexFilter::filter(hepfw::Event &event){
  
  vector<ic::Vertex> *evVertices = event.getByName< vector<ic::Vertex> >(m_inputLabel);
  
  if(!(evVertices->size()>m_minNVertex)){return false;}
  
  // If any conditions over the PV we do those
  if(
    m_doPV_minNTracks ||
    m_doPV_minChi2 ||
    m_doPV_minNDof ||
    m_doPV_maxZ ||
    m_doPV_maxRho
  ){
    
    // We get the PV
    if(evVertices->size()==0){return false;}
    ic::Vertex *pvVertex = &(*evVertices)[0];
    
    if(m_doPV_minNTracks){if(!(pvVertex->tracks().size()   >  m_pv_minNTracks)){return false;}}
    if(m_doPV_minChi2)   {if(!(pvVertex->chi2()            >  m_pv_minChi2))   {return false;}}
    if(m_doPV_minNDof)   {if(!(pvVertex->ndof()            >  m_pv_minNDof))   {return false;}}
    if(m_doPV_maxZ)      {if(!(fabs(pvVertex->point().z()) <= m_pv_maxZ))      {return false;}}
    if(m_doPV_maxRho)    {if(!(pvVertex->point().rho()     <  m_pv_maxRho))    {return false;}}
  }

  // Emulating !isFake() but for this ntuples is always nTrack=0 since we are not storing tracks
  //if(pvVertex->chi2()==0 && pvVertex->ndof()==0 && pvVertex->tracks().size()==0){return false;}
  //
  //// Other vertex conditions
  //if(pvVertex->ndof()            <= 4) {return false;}
  //if(fabs(pvVertex->point().z()) >  24){return false;}
  //if(pvVertex->point().rho()     >= 2) {return false;}
  
  return true;
}
