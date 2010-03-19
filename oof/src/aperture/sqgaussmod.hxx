/**
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   Initial version March 2010

   \file sqgaussmod.hxx

*/
#ifndef __OOF_SQGAISSMOD_HXX__
#define __OOF_SQGAISSMOD_HXX__

#include <boost/scoped_ptr.hpp>

#include "amplimod.hxx"

// Forward declarations in AstroMap
namespace AstroMap {
  class Map;
}

namespace OOF {

  // Forward declarations
  class TelGeometry;
  
  /** \brief "Squashed" Gaussian profile for aperture illumination
   */
  class SqGaussMod:
    public AmpliMod
  {

    /// Square of the radius of the dish
    const double effrad2;

  public:

    // ------------------ Public data -----------------------------
    double amp, sigma, x0, y0;
    

    // ------------------ Construction / Destruction --------------

    SqGaussMod(TelGeometry *telgeo, 
	       AstroMap::Map &msample);
    
    virtual ~SqGaussMod(void);


    // ----- Inherited from AmpliMod  ------------------------------

    virtual void Calc(AstroMap::Map &m) const;
      
    // ------ Inherited functions rom Minim::Model ---------
      
    virtual void AddParams(std::vector< Minim::DParamCtr > &pars);
    
  };

}


#endif
