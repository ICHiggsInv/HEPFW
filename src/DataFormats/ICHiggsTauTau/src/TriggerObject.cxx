#include "DataFormats/ICHiggsTauTau/interface/TriggerObject.h"
#include "DataFormats/ICHiggsTauTau/interface/city.h"
#include "boost/format.hpp"

namespace ic {
  //Constructors/Destructors
  TriggerObject::TriggerObject() {
  }

  TriggerObject::~TriggerObject() {
  }

  void TriggerObject::Print() const {
    Candidate::Print();
  }
}
