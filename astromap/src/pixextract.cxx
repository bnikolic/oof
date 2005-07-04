/*
  Bojan Nikolic
  $Id: pixextract.cxx,v 1.1 2005/07/04 22:23:09 bnikolic Exp $

*/

#include "pixextract.hxx"

#include "astromap.hxx"

namespace AstroMap {

  PixListInt::PixListInt(size_t npix):
    px ( new std::valarray<int>(npix)),
    py ( new std::valarray<int>(npix))
  {
  }

  PixListInt::PixListInt(const PixListInt &p):
    px ( new std::valarray<int> (* (p.px) ) ),
    py ( new std::valarray<int> (* (p.py) ) )
  {
  }

  
  PixListInt ExSquare( int cx, int cy , int halflen_px, Map &m)
  {
    
    int xmin = cx - halflen_px;
    if ( xmin < 0)
      xmin =0;
    if ( xmin >= (signed) m.nx ) 
      xmin = m.nx -1 ;

    int xmax = cx + halflen_px;
    if ( xmax < 0)
      xmax =0;
    if ( xmax >= (signed) m.nx ) 
      xmax = m.nx -1 ;

    int ymin = cy - halflen_px;
    if ( ymin < 0)
      ymin =0;
    if ( ymin >= (signed) m.ny ) 
      ymin = m.ny -1 ;

    int ymax = cy + halflen_px;
    if ( ymax < 0)
      ymax =0;
    if ( ymax >= (signed) m.ny ) 
      ymax = m.ny -1 ;

    size_t npix = (xmax- xmin +1 ) * ( ymax- ymin +1 );

    PixListInt res (npix);

    size_t count=0;
    for (int i (xmin) ; i  <= xmax ; ++i )
      for (int j (ymin) ; j  <= ymax ; ++j )
	{
	  (*res.px)[count] = i;
	  (*res.py)[count] = j;
	  count++;
	}

    return res;

  }


}


