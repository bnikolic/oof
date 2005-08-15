/*
  Bojan Nikolic
  $Id: obscompare.hxx,v 1.3 2005/08/15 15:45:45 bnikolic Exp $

  Compare models to observations!
*/

#ifndef __OOF_OBSCOMPARE_HXX__
#define __OOF_OBSCOMPARE_HXX__

#include <minimmodel.hxx>

#include <astromap_fwd.hxx>
#include <vector>

namespace OOF {

  // Forward declarations
  class ApertureMod;
  class ObsPhaseScreen;
  class MapToResidual;

  /*! This class compares a set of observations against predictions of
   *  an aperture model and returns the residuals.  It also enumerates
   *  the free parameters and hence allows for minimisations of the
   *  residuals
   */
  class ObsCompare : public Minim::Minimisable {
    
    /*! This is the model for the aperture. This class will own the
     * pointer. */
    ApertureMod * aperture;
    

    /*! Each observation can have its own phase screen, typically this
     *   is a defocus */
    std::vector<ObsPhaseScreen *> phasescreens;

    /*! These classes contain the actuall observed data and they
     *  return the residuals  */
    std::vector<MapToResidual *> rescalculators;

    /// A scratch map for calculating apertures
    AstroMap::Map *ApScratch;

    /// A scratch map for calculating dephased apertures
    AstroMap::Map * ApScratchDephase;

  public:
    
    // ------- Constructors / Destructors    -----------
    ObsCompare( ApertureMod * aperture,
		AstroMap::Map &apsample );		

    virtual ~ObsCompare(void) ;

    // ------- Member functions -----------------------

    /*! Add an observation to the current set. Note ownership of both
     *  pointers will be taken. */
    void AddObs( MapToResidual * rc , ObsPhaseScreen * ps);

    /*! Return the number of observations in this set */
    unsigned NObs(void);


    // ------- Methods inherited from minimisable

    virtual void  residuals ( std::vector< double > & res ) ;
    virtual unsigned   nres (void)   ; 
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars ) ;



  };

  


}

#endif
