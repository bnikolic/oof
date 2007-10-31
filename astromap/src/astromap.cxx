/**
   \file astromap.cxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   2004-2007
*/

#include "astromap.hxx"


#include <bndebug.hxx>
#include <cmath>

#include "coordsys/coordsys.hxx"
#include "coordsys/lincordsys.hxx"


namespace AstroMap {

  Map::Map(unsigned nx , unsigned ny ):
    MapBase( nx* ny),
    nx(nx),
    ny(ny),
    cs(new LinCS() )
  {

  }

  Map::Map(unsigned nx , unsigned ny, CoordSys *cs ):
    MapBase( nx* ny),
    nx(nx),
    ny(ny),
    cs(cs)
  {
  }

  Map::Map(const Map& m):
    MapBase( dynamic_cast<const MapBase & >(m) ),
    nx(m.nx),
    ny(m.ny),
    cs(m.cs->Clone() )
  {

  }

  Map::~Map()
  {
    delete cs;
  }


  const Map & Map::operator= (const Map & m) 
  {
    ENFORCE( nx == m.nx && ny == m.ny );

    (*dynamic_cast<MapBase * >(this)) = dynamic_cast<const MapBase & >(m);

    if (cs) 
      delete cs;
    cs=m.cs->Clone();

    return *this;
    
  }

  double & Map::get(unsigned x , unsigned y )
  {
    return (*this)[y*nx+x];
  }

  const double & Map::get(unsigned x , unsigned y ) const
  {
    return (*this)[y*nx+x];
  }

  void Map::sqrt(void)
  {
    (*dynamic_cast<MapBase * >(this)) = std::sqrt(*this);    
  }

  void Map::min_max_fin(double & minval, double &maxval)
  {
    double rmax, rmin;
    size_t i =0 ;
    while ( ! std::isfinite (  (*this)[i] ) )
    {
      ++i;
    }
    rmax=rmin=  (*this)[i] ;

    for (  ; i < size() ; ++i)
    {
      double x = (*this)[i];
      if ( std::isfinite ( x ) && x < rmin )
      {
	rmin= x;
      }
      if ( std::isfinite ( x ) && x > rmax )
      {
	rmax=x;
      }
      
    }
    minval=rmin;
    maxval=rmax;

  }

  Map * Clone (Map &m)
  {
    return new Map( m.nx, m.ny, m.cs->Clone());
  }



}
