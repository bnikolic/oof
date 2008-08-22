/**
   \file astromap_err.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>   
   
   Exceptions for errors in AstroMap
*/
#ifndef _ASTROMAP_ASTROMAP_ERR_HXX__
#define _ASTROMAP_ASTROMAP_ERR_HXX__

#include <stdexcept>
#include <boost/utility.hpp>


namespace AstroMap{

  /** \brief Base class for errors caused by incorrect usage of
      AstroMap library
   */
  class UseError :
    public std::runtime_error
  {

  public:
    
    UseError(const std::string &w);

    virtual ~UseError() throw()
    {};

  };

  /**
     \brief Errors arising due to invalid indexing 
  */
  class IndexingError :
    private boost::base_from_member<std::string>,
    public UseError
  {

  public:

    IndexingError(int i, int j,
		  const std::string &w);

    virtual ~IndexingError() throw()
    {}

  };

}

#endif
