/**
   \file mapdsutils.cxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>

   September 2007
*/

#include "mapdsutils.hxx"

#include <memory>

#include "../astromap.hxx"
#include "../coordsys/coordsys.hxx"
#include "dataseries.hxx"

namespace AstroMap {

  DataSeries * MapToDSPoss( const Map & m)
  {
    size_t np = m.nx * m.ny ;

    std::auto_ptr<DataSeries> res( new DataSeries( np));

    for(size_t y = 0 ; y < m.ny ; ++y)
    {
      for (size_t x = 0 ; x < m.nx ; ++x )
      {
	(*res)[y*m.nx+x].dX = m.cs->x_pxtoworld( x,y) ;
	(*res)[y*m.nx+x].dY = m.cs->y_pxtoworld( x,y) ;
	(*res)[y*m.nx+x].fnu=0;
	(*res)[y*m.nx+x].ufnu=0;

      }
    }


    return res.release();

  }

  

}

