#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"

namespace ic {
  //Constructors/Destructors
  GenParticle::GenParticle() {
  }

  GenParticle::~GenParticle() {
  }

  void GenParticle::Print() const {
    Candidate::Print();
  }
}
