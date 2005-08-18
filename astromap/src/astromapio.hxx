/*
  Bojan Nikolic
  $Id: astromapio.hxx,v 1.3 2005/08/18 17:56:07 bnikolic Exp $

  Input/Output routines for astromap
*/
#ifndef __ASTROMAP_ASTROMAPIO_HXX__
#define __ASTROMAP_ASTROMAPIO_HXX__

#include <bnfits_fwd.hxx>

#include <vector>

namespace AstroMap {

  // forwards
  class Map;

  // Reading routines

  Map * FitsMapLoad ( BNFits::FitsF &fout );

  Map * FitsMapLoad ( const char * fnamein, int extno);

  // Writing routines

  void FitsWrite ( Map & m,
		   BNFits::FitsF &fout);

  void FitsWrite ( Map & m,
		   const char * fnameout );

  void FitsWrite ( std::vector<Map *> mvect,
		   const char * fnameout );
  


}


#endif
