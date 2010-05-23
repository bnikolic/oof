/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2008

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file bnmin_main.cxx

*/

#include <sstream>

#include <boost/format.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

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
    
  
  std::string concat(const std::string &s,
		     const boost::numeric::ublas::matrix<double> &m)
  {
    std::ostringstream o;
    o<<s<<m;
    return o.str();
  }

  MatrixErr::MatrixErr(const std::string &s,
		       const boost::numeric::ublas::matrix<double> &m):
    BaseErr(concat(s, m))
  {
  }


}


