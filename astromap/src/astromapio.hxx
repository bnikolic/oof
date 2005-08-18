/*
  Bojan Nikolic
  $Id: astromapio.hxx,v 1.2 2005/08/18 15:09:46 bnikolic Exp $

  Input/Output routines for astromap
*/
#ifndef __ASTROMAP_ASTROMAPIO_HXX__
#define __ASTROMAP_ASTROMAPIO_HXX__

#include <bnfits_fwd.hxx>

#include <vector>

namespace AstroMap {

  // forwards
  class Map;

  void FitsWrite ( Map & m,
		   BNFits::FitsF &fout);

  void FitsWrite ( Map & m,
		   const char * fnameout );

  void FitsWrite ( std::vector<Map *> mvect,
		   const char * fnameout );
  


}


#endif
