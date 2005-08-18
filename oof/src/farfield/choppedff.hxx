/*! 
  Bojan Nikolic
  $Id: choppedff.hxx,v 1.2 2005/08/18 23:52:32 bnikolic Exp $

  Support for chopped observations
*/

#ifndef _OOF_CHOPPEDFF_HXX___
#define _OOF_CHOPPEDFF_HXX___

#include "farf.hxx"

namespace OOF {

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

    virtual void Power ( const AstroMap::Map & amp, AstroMap::Map & phase, AstroMap::Map & res);

    // ------ Inherited functions rom Minim::Model ---------
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );    

  };

  

  

}

#endif
