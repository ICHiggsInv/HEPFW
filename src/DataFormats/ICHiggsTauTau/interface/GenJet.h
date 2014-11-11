#ifndef ICHiggsTauTau_GenJet
#define ICHiggsTauTau_GenJet

#include "Rtypes.h"
#include "Math/Point3D.h"
#include "Math/Point3Dfwd.h"
#include <vector>
#include "DataFormats/ICHiggsTauTau/interface/Candidate.h"


namespace ic {


  class GenJet : public Candidate {

    public:
      GenJet();
      virtual ~GenJet();

      inline int flavour() const { return flavour_; }
      inline void set_flavour(int const& flavour) { flavour_ = flavour; }

      inline unsigned n_constituents() const { return n_constituents_; }
      inline void set_n_constituents(unsigned const& n_constituents) { n_constituents_ = n_constituents; }
      
      inline std::vector<std::size_t> const& constituents() const { return constituents_; }
      inline void set_constituents(std::vector<std::size_t> const& constituents) { constituents_ = constituents; }
      
      virtual void Print() const;


    private:
      int flavour_;
      unsigned n_constituents_;
      std::vector<unsigned long> constituents_;
  public:
    ClassDef(GenJet,1);
  };

  typedef std::vector<ic::GenJet> GenJetCollection;

}
#endif
