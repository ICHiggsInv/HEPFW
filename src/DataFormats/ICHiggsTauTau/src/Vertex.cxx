#include "DataFormats/ICHiggsTauTau/interface/Vertex.h"

namespace ic {
  //Constructors/Destructors
  Vertex::Vertex() : point_(Point()), id_(0) {
  }

  Vertex::~Vertex() {
  }

  void Vertex::Print() const {
    std::cout << point_ << std::endl;
  }
}
