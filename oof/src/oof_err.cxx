/**
   \file oof_err.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>      
*/

#include "oof_err.hxx"

#include <boost/format.hpp>

namespace  OOF {
  
  UseError::UseError(const std::string &w):
    std::runtime_error(w)
  {
  }

  NObsError::NObsError(size_t expectedN, 
		       size_t suppliedN, 
		       const std::string &extratext):
    boost::base_from_member<std::string>(formatMsg(expectedN, 
						   suppliedN, 
						   extratext)),
    UseError(member)
  {
  }

  std::string NObsError::formatMsg(size_t expectedN, 
				   size_t suppliedN, 
				   const std::string &extratext)
  {
    return (boost::format("Inconsistent number of observations: expected %i, supplied %i; ") 
	    %expectedN 
	    %suppliedN).str() + extratext;
  }
    

}

   
