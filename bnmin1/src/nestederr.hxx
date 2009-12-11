/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2009

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file nestederr.hxx

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
