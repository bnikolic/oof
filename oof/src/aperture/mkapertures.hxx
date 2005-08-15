/*!
  Bojan Nikolic
  $Id: mkapertures.hxx,v 1.1 2005/08/15 21:57:46 bnikolic Exp $

  Functions to make apertures...
*/

#ifndef __OOF_MKAPERTURES_HXX__
#define __OOF_MKAPERTURES_HXX__

#include <astromap_fwd.hxx>


namespace  OOF {

  // Forwards
  class ApertureMod;
  class TelGeometry;

  /*! Make an aperture map  */
  AstroMap::Map * MkApMap ( TelGeometry * telgeo ,
			    unsigned npix,
			    double oversample);

  /*! Make the standard aperturemod class used: zernike phase,
  gaussian * illumination */

  ApertureMod * MkSimpleAp( TelGeometry * telgeo ,
			    double wavel,
			    unsigned npix,
			    unsigned nzern ,
			    double oversample );



}

#endif
