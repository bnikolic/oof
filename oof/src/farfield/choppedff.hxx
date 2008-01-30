/**
   \file choppedff.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>

   Support for chopped observations
*/

#ifndef _OOF_CHOPPEDFF_HXX___
#define _OOF_CHOPPEDFF_HXX___

#include "farf.hxx"

namespace OOF {

  /**
     \brief Represent a differenced or chopped on-the sky measurement
     by the telescope.
   */
  class ChoppedFF : public FarF {

    /*! An aperutre phase map representing a vertical tilt
     *  corresponding to a deflection of a unit radian. */
    AstroMap::Map * vaptilt ;
    
    /*! An aperutre phase map representing a horizontal tilt */
    AstroMap::Map * haptilt ;
    
    /*! Also need an phase scratch */
    AstroMap::Map * phasescratch ;

    /*! And an sky scratch...*/
    AstroMap::Map * skyscratch ;
    

  public:

    // Vertical chop in radians
    double vchop;

    // Horizontal chop in radians
    double  hchop;

    /*! The relative strengths of positive and negative beams ( neg =
     *  pos * -1 *beamgainf). Oft required for dual/multi receiver
     *  systems that arent properly flatfielded.
     */
    double beamgainf;

    // ---------- Constructors / destructors    -------------
    
    ChoppedFF( AstroMap::Map & apmapsample, double wavel );

    virtual ~ChoppedFF();

    // ---------- Functions inherited from FarF  -------------

    virtual void Power ( const AstroMap::Map & amp, 
			 const AstroMap::Map & phase, 
			 AstroMap::Map & res);

    virtual const char * FFType (void) const; 

    // ------ Inherited functions rom Minim::Model ---------
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );    

  };

  

  

}

#endif
