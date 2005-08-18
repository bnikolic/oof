/*
  Bojan Nikolic
  $Id: csfileio.hxx,v 1.2 2005/08/18 18:33:23 bnikolic Exp $

  File input / output for coordinate systems.
*/

#ifndef _ASTROMAP_CSFILEIO_HXX__
#define _ASTROMAP_CSFILEIO_HXX__

#include <bnfits_fwd.hxx>

namespace AstroMap {

  class CoordSys ;

  /*! Write out the supplied coordinate system to the current header
    of the supplied fits file*/
  void FitsWrite(  CoordSys & cs, BNFits::FitsF & fout,
		   int nx, int ny);

  CoordSys * FitsCSLoad( BNFits::FitsF & fin );
  


}

#endif
