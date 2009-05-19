/**
   \file bnmin_main.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>

*/

#include "bnmin_main.hxx"
#include "../config.h"

namespace Minim {

  const char * version(void)
  {
    return PACKAGE_VERSION;
  }

  BaseErr::BaseErr(const std::string &s):
    std::runtime_error(s)
  {
  }


}


