/*!
  Bojan Nikolic
  $Id: phasemod.cxx,v 1.3 2005/08/24 21:21:14 bnikolic Exp $

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


