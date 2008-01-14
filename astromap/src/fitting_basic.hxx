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
#include "astromap.hxx"
#include "gaussian.hxx"

// Forward declarations
namespace BNLib{
  class BinaryDD;
}

namespace AstroMap {

  /**
     \brief Fit single functions of two variables to a region in a map.
     
   */
  class FittableMap :
    public Minim::Minimisable
  {
    BNLib::BinaryDD & model;
    const Map & map;

    /// A scratch map to compute the model on
    Map mtemp;

  public:
    // ---------- Construction/Destruction -------------

    /**
       \param The model to be fitted for
       \param map the map to fit for. 
       
       \note still need to add parameters after construction
     */
    FittableMap(BNLib::BinaryDD & model,
		const Map       & map);

    // ---------- Public interface         -------------

    // ---------- Inherited from Minimisable -----------
    
    virtual void  residuals ( std::vector< double > & res ) ;
    virtual unsigned   nres (void)  ; 

  };

  /**
     \brief Fit a gaussian to a map.
   */
  class GaussMapModel {
    
  public:

    // ---------- Public data ------------

    /**
       The gaussian model. Publicly expose for easy introspection.
     */
    BNLib::GaussianDD gm;
    
    FittableMap fm;

    // ------------ Construction/ destruction ----------
    
    GaussMapModel( const Map       & map);
    
    

  };

}

#endif // HAVE_MINIMMODEL_HXX

#endif
