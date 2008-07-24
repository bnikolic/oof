/**
   \file obsdefocus.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>   
*/

#ifndef _OOF_OBSDEFOCUS_HXX__
#define _OOF_OBSDEFOCUS_HXX__

#include "obsphasescreen.hxx"

namespace OOF {

  // Forwards
  class TelGeometry;


  class ObsDefocus : public ObsPhaseScreen {


    /*! This is the actuall screen that will be applied */
    AstroMap::Map  * screen;

    /*! This the amount of defocus */
    double dz;

  public:

    // --------   Constructors / Destructors   ---------------------

    /*! Construct a defocus screen. In simplest scenario the defocus
     * is fixed so no need to keep any information other than the
     * actual phase screen. Even if dz is adjustable, so far have only
     * encountered linear relations in defocus anyway.
     */
    ObsDefocus ( TelGeometry * telgeo , AstroMap::Map  & apmapsample, double dz,
		 double wavel);

    virtual ~ObsDefocus();

    // ---------  Methods inherited from ObsPhaseScreen -------------
    
    virtual void DePhase( AstroMap::Map  & res) ;


  };


}

#endif
