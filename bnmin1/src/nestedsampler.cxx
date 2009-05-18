/**
   \file nestedsampler.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include "nestedsampler.hxx"

namespace Minim {

  NestedS::NestedS(MLikelihood & ml,
		   std::list<MCPoint> start,
		   const std::vector<double> & sigmas,
		   unsigned seed):
    Zseq(1,0.0),
    Xseq(1,0.0),
    ml(ml)
  {
  }

  NestedS::~NestedS(void)
  {
  }

}


