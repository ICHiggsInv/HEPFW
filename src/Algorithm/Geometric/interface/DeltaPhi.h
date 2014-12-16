#ifndef Algorithm_Geometric_DeltaPhi
#define Algorithm_Geometric_DeltaPhi

/* functions to compute deltaPhi 
 * 
 * Imported from CMSSW and originally ported from original code in RecoJets 
 * by Fedor Ratnikov, FNAL
 */

#include <cmath>

namespace hepfw {

  inline double deltaPhi(double phi1, double phi2) { 
    double result = phi1 - phi2;
    while (result > M_PI) result -= 2*M_PI;
    while (result <= -M_PI) result += 2*M_PI;
    return result;
  }

  inline double deltaPhi(float phi1, double phi2) {
    return deltaPhi(static_cast<double>(phi1), phi2);
  }
  
  inline double deltaPhi(double phi1, float phi2) {
    return deltaPhi(phi1, static_cast<double>(phi2));
  }
  

  inline float deltaPhi(float phi1, float phi2) { 
    float result = phi1 - phi2;
    while (result > float(M_PI)) result -= float(2*M_PI);
    while (result <= -float(M_PI)) result += float(2*M_PI);
    return result;
  }

  template<typename T1, typename T2>
    inline double deltaPhi(T1& t1, T2 & t2) {
    return deltaPhi(t1.phi(), t2.phi());
  }      

  template <typename T> 
    inline T deltaPhi (T phi1, T phi2) { 
    T result = phi1 - phi2;
    while (result > M_PI) result -= 2*M_PI;
    while (result <= -M_PI) result += 2*M_PI;
    return result;
  }

}

// For sorting
using hepfw::deltaPhi;

template<typename T1, typename T2 = T1>
struct DeltaPhi {
  double operator()(const T1 & t1, const T2 & t2) const {
    return hepfw::deltaPhi(t1, t2);
  }
};

#endif