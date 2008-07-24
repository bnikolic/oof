/**
   \file oof_err.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>      
   
   Exception hirearchy for errors in OOF
*/
#ifndef _OOF_OOF_ERR_HXX__
#define _OOF_OOF_ERR_HXX__

#include <stdexcept>
#include <boost/utility.hpp>

namespace  OOF {

  /** 
      \brief Base class for errors caused by incorrect usage of the library
   */
  class UseError :
    public std::runtime_error
  {

  public:
    
    UseError(const std::string &w);

  };

  /** \brief Errors due to inconsistent number of observations in set
   */
  class NObsError :
    private boost::base_from_member<std::string>,
    public UseError
  {
    
    static std::string formatMsg(size_t expectedN, 
				 size_t suppliedN, 
				 const std::string &extratext);
    
  public:

    NObsError(size_t expectedN, 
	      size_t suppliedN, 
	      const std::string &extratext);

  };


}
#endif
   
