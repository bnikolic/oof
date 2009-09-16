/**
   \file bnmin_main.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>

*/

#include <boost/format.hpp>

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

  NParsErr::NParsErr(const std::string &fname,
		     size_t expected,
		     size_t received):
    BaseErr( (boost::format("In function %s expected %i but received %i pars ") 
	      % fname
	      % expected
	      % received).str())
  {
  }
    



}


