/**
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version November 2009

   \file nestedinitial.cxx

*/

#include <set>

#include "nestedinitial.hxx"
#include "nestedsampler.hxx"


namespace Minim {

  const MCPoint & InitialWorst::operator()(const NestedS &ns)
  {
    std::set<MCPoint>::iterator worst (-- ns.g_ss().end());
    return worst->p;
  }


}


