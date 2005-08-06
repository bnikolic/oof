/*
  Bojan Nikolic
  $Id: tmapset.hxx,v 1.3 2005/08/06 14:46:55 bnikolic Exp $

  Templated functions to set maps
*/

#ifndef _ASTROMAP_TMAPSET_HXX__
#define _ASTROMAP_TMAPSET_HXX__

#include "astromap.hxx"

#include "coordsys/coordsys.hxx"

namespace AstroMap {

  template<class FnT> void TWorldSet(Map &m , FnT &fn )
  {
    double wx;
    double wy;

    for (unsigned px (0) ; px < m.nx ; ++px)
      {
	for (unsigned py(0) ; py < m.ny ; ++py )
	  {
	    // Get the world coordinates of this pixel
	    m.cs->pxtoworld(px , py , wx, wy );

	    m.get(px, py ) = fn(wx, wy);
	    
	  }

      }

  }


  template<class FnT> void TWorldSet(Map &m , FnT &fn , const std::valarray<bool> &  mask )
  {
    double wx;
    double wy;
    
    size_t i = 0;
    for (unsigned px (0) ; px < m.nx ; ++px)
      {
	for (unsigned py(0) ; py < m.ny ; ++py )
	  {
	    if (mask[i] ) 
	      {
		// Get the world coordinates of this pixel
		m.cs->pxtoworld(px , py , wx, wy );
		m.get(px, py ) = fn(wx, wy);
	      }
	    ++i;
	  }
      }
  }


}

#endif 
