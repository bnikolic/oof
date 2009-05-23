/**
   \file nestederr.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Error hirearchy for the nested sampler
*/

#ifndef _BNMIN1_NESTEDERR_HXX__
#define _BNMIN1_NESTEDERR_HXX__

#include <list>

#include "bnmin_main.hxx"

#include "mcpoint.hxx"

namespace Minim {

  /** Error 
   */
  class NestedSmallStart:
    public BaseErr
  {
    
  public:
    
    NestedSmallStart(const std::list<MCPoint> &ss);     

  };




}

#endif
