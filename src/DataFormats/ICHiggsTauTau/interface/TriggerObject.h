#ifndef ICHiggsTauTau_TriggerObject
#define ICHiggsTauTau_TriggerObject

#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"
#include "Math/Point3D.h"
#include "Math/Point3Dfwd.h"
#include <map>
#include <string>
#include "DataFormats/ICHiggsTauTau/interface/Candidate.h"


namespace ic {


  class TriggerObject : public Candidate {

    private:

    public:
      TriggerObject();
      virtual ~TriggerObject();

      inline std::vector<std::size_t>  const& filters() const { return filters_; }
      inline void set_filters(std::vector<std::size_t>  const& filters) { filters_ = filters; }

      virtual void Print() const;

    private:
      std::vector<std::size_t> filters_;

  };

  typedef std::vector<ic::TriggerObject> TriggerObjectCollection;

}
#endif
