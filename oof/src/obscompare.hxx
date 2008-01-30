/*
  Bojan Nikolic
  $Id: obscompare.hxx,v 1.8 2005/08/18 23:52:32 bnikolic Exp $

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
  class FarF;

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

    /// A scratch map for the far-field power
    AstroMap::Map * SkyScratch;    

    /*! This will be used to turn aperture distributions in far field
     * distributions
     */
    FarF * farf;


  public:
    
    // ------- Constructors / Destructors    -----------

    /*! The simplest constructor, make our own farfield class so there
     *  can beq nothing fancy about observations, i.e., just a simple
     *  beam measurement.
     */
    ObsCompare( ApertureMod * aperture,
		AstroMap::Map &apsample );		

    ObsCompare( ApertureMod * aperture,
		AstroMap::Map &apsample,
		FarF * customff);		

    virtual ~ObsCompare(void) ;

    // ------- Member functions -----------------------

    /*! Add an observation to the current set. Note ownership of both
     *  pointers will be taken. */
    void AddObs( MapToResidual * rc , ObsPhaseScreen * ps);

    /*! Return the number of observations in this set */
    unsigned NObs(void);

    /*! Return the model beam for the ith observation */
    void  Beam (unsigned i , AstroMap::Map & res );

    /*! Return the model beam for the ith observation */
    AstroMap::Map *  Beam (unsigned i  );

    /*! Return just the plain beam  */
    AstroMap::Map *  Beam (void  );

    /*! Return the aperture */
    ApertureMod * GetAperture(void);

    /** \brief Return pointer to the farfield 
	
	\note This is a trouble-shooting function
     */
    const FarF * getFF(void) { return farf; };
    
    


    // ------- Methods inherited from minimisable

    virtual unsigned   nres (void)   ; 
    virtual void  residuals ( std::vector< double > & res ) ;
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars ) ;



  };

  


}

#endif
