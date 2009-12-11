/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version November 2009

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file nestedinitial.cxx

*/

#include <set>
#include <iostream>

#include "nestedinitial.hxx"
#include "nestedsampler.hxx"


namespace Minim {

  NestedInitial::~NestedInitial()
  {
  }

  const MCPoint & InitialWorst::operator()(const NestedS &ns)
  {
    std::set<MCPoint>::iterator worst (-- ns.g_ss().end());
    return *worst;
  }

  InitialRandom::InitialRandom(size_t n_ss):
    gen(0,n_ss-1)
  {
  }
  
  const MCPoint & InitialRandom::operator()(const NestedS &ns)
  {
    size_t i= gen(eng);

    std::set<MCPoint>::iterator p (ns.g_ss().begin());
    for (size_t j=0; j<i; ++j)
      ++p;

    return *p;

  }


}


