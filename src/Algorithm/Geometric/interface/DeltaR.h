#ifndef Algorithm_Geometric_DeltaR
#define Algorithm_Geometric_DeltaR

/* functions to compute deltaR
 * 
 * Imported from CMSSW and originally ported from original code in RecoJets 
 * by Fedor Ratnikov, FNAL
 */

#include <cmath>

namespace hepfw {

  template<typename T1, typename T2>
  inline double  deltaR2(const T1 & t1, const T2 & t2) {
    typedef  double Float;
    Float p1 = t1.phi(); 
    Float p2 = t2.phi(); 
    Float e1 = t1.eta(); 
    Float e2 = t2.eta(); 
    double dp=std::abs(p1-p2); if (dp>Float(M_PI)) dp-=Float(2*M_PI);  
    return (e1-e2)*(e1-e2) + dp*dp;
  } 
  
  // do not use it: always cut in deltaR2!
  template<typename T1, typename T2>
  inline  double deltaR(const T1 & t1, const T2 & t2) {
    return std::sqrt(deltaR2(t1,t2));
  } 

  template <class T1, class T2, class T3, class T4>
  inline
  T1 deltaR2 (T1 eta1, T2 phi1, T3 eta2, T4 phi2) {
    T1 deta = eta1 - eta2;
    T1 dphi = std::abs(phi1-phi2); if (dphi>T1(M_PI)) dphi-=T1(2*M_PI);  
    return deta*deta + dphi*dphi;
  }

  // to be avoided
  template <class T1, class T2, class T3, class T4>
  inline
  T1 deltaR (T1 eta1, T2 phi1, T3 eta2, T4 phi2) {
    return std::sqrt (deltaR2 (eta1, phi1, eta2, phi2));
  }

}

// For sorting
using hepfw::deltaR2;
using hepfw::deltaR;

// obsolete use lambdas (and cut in deltaR2!)
template<typename T1, typename T2 = T1>
struct DeltaR {
  double operator()( const T1 & t1, const T2 & t2 ) const {
    return hepfw::deltaR(t1, t2);
  }
};

#endif