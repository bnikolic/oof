/**
  \file fitting_basic.hxx
  Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>
  Initial version January 2008.
  
  Basic fitting routines on maps.

*/
#ifndef _ASTROMAP_FITTING_BASIC_HXX__
#define _ASTROMAP_FITTING_BASIC_HXX__

#include "../config.h"

#if HAVE_MINIMMODEL_HXX

#include "minimmodel.hxx"

namespace AstroMap {

  /**
     \brief Fit single functions of two variables to a region in a map.
     
   */
  class FittableMap :
    public Minim::Minimisable
  {

  public:
    // ---------- Construction/Destruction -------------
    FittableMap();

    // ---------- Inherited from Minimisable -----------
    
    virtual void  residuals ( std::vector< double > & res ) = 0;
    virtual unsigned   nres (void)  =0 ; 

  };

}

#endif // HAVE_MINIMMODEL_HXX

#endif
