/**
   \file astromap_err.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>   
*/

#include "astromap_err.hxx"

#include <boost/format.hpp>

namespace AstroMap{

  UseError::UseError(const std::string &w):
    std::runtime_error(w)
  {
  }

  IndexingError::IndexingError(int i, int j,
			       const std::string &w):
    boost::base_from_member<std::string>( w + (boost::format(" at pixel (%i,%i) ") %i %j).str()),
    UseError(member)
  {
    
  }

}

