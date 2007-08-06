/**
   \file pixextract.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>
*/

#include "pixextract.hxx"

#include "astromap.hxx"
#include "coordsys/coordsys.hxx"

namespace AstroMap {

  PixListInt::PixListInt(size_t npix):
    px ( npix),
    py ( npix)
  {
  }

  PixListInt::PixListInt(const PixListInt &p):
    px ( p.px ),
    py ( p.py )
  {
  }

  
  PixListInt ExSquare( int cx, int cy , int halflen_px, Map  const &m)
  {

    int xmin = cx - halflen_px;
    if ( xmin < 0)
      xmin =0;
    if ( xmin >= (signed) m.nx ) 
      return PixListInt(0);

    int xmax = cx + halflen_px;
    if ( xmax < 0)
      return PixListInt(0);
    if ( xmax >= (signed) m.nx ) 
      xmax = m.nx -1 ;

    int ymin = cy - halflen_px;
    if ( ymin < 0)
      ymin =0;
    if ( ymin >= (signed) m.ny ) 
      return PixListInt(0);

    int ymax = cy + halflen_px;
    if ( ymax < 0)
      return PixListInt(0);
    if ( ymax >= (signed) m.ny ) 
      ymax = m.ny -1 ;

    size_t npix = (xmax- xmin +1 ) * ( ymax- ymin +1 );

    PixListInt res (npix);

    size_t count=0;
    for (int i (xmin) ; i  <= xmax ; ++i )
      for (int j (ymin) ; j  <= ymax ; ++j )
	{
	  res.px[count] = i;
	  res.py[count] = j;
	  count++;
	}

    return res;

  }

  size_t PixListInt::size(void) 
  {
    return px.size();
  }

  void GetNearestPixel( const Map & m,
			double cx, double cy,
			int & pxOUT, int & pyOUT )
  {
    double px, py;
    m.cs->worldtopx( cx  , cy , px, py);

    int i_px = lrint(px);
    if (i_px < 0 )
      i_px=0;
    if (i_px >= (int) m.nx)
      i_px = m.nx-1;

    int i_py = lrint(py);
    if (i_py < 0 )
      i_py=0;
    if (i_py >= (int) m.ny)
      i_py = m.ny-1;

    pxOUT=i_px;
    pyOUT=i_py;

  }

}


