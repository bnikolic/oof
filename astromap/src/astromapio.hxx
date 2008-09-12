/**
   \file astromapio.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>

   Input/Output routines for astromap
*/
#ifndef __ASTROMAP_ASTROMAPIO_HXX__
#define __ASTROMAP_ASTROMAPIO_HXX__

#include <bnfits_fwd.hxx>
#include <fitserr.hxx>

#include <vector>


namespace AstroMap {

  // forwards
  class Map;

  // Reading routines

  Map * FitsMapLoad ( BNFits::FitsF &fout );

  Map * FitsMapLoad ( const char * fnamein, int extno) throw (BNFits::FIOExc);

  // Writing routines

  void FitsWrite ( Map & m,
		   BNFits::FitsF &fout) throw (BNFits::FIOExc);

  void FitsWrite ( Map & m,
		   const char * fnameout ) throw (BNFits::FIOExc);

  void FitsWrite ( std::vector<Map *> mvect,
		   const char * fnameout );
  


}


#endif
