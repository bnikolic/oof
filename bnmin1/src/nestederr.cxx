/**
   \file nestederr.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include "nestederr.hxx"

namespace Minim {

  NestedSmallStart::NestedSmallStart(const std::list<MCPoint> &ss):
    BaseErr("Number of points in the starting set is less than two")
  {
  }


}


