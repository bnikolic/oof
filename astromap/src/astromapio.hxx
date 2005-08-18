/*
  Bojan Nikolic
  $Id: astromapio.hxx,v 1.1 2005/08/18 04:56:18 bnikolic Exp $

  Input/Output routines for astromap
*/
#ifndef __ASTROMAP_ASTROMAPIO_HXX__
#define __ASTROMAP_ASTROMAPIO_HXX__


namespace AstroMap {

  // forwards
  class Map;

  void FitsWrite ( Map & m,
		   const char * fnameout );
  


}


#endif
