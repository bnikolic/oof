/**
   \file phasemod.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>

*/

#include "phasemod.hxx"

namespace OOF {

  PhaseMod::~PhaseMod(void)
  {
  }

  Minim::Model * PhaseMod::downcast(void)
  {
    return this;
  }


}


