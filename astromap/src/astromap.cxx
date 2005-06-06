/*
  Bojan Nikolic
  $Id: astromap.cxx,v 1.2 2005/06/06 13:37:05 bnikolic Exp $

*/

#include "astromap.hxx"

namespace AstroMap {

  Map::Map(unsigned nx , unsigned ny ):
    MapBase( nx* ny),
    nx(nx),
    ny(ny)
  {

  }

  double & Map::get(unsigned x , unsigned y )
  {
    return (*this)[y*nx+x];
  }

  const double & Map::get(unsigned x , unsigned y ) const
  {
    return (*this)[y*nx+x];
  }

  Map * Clone (Map &m)
  {
    return new Map( m.nx, m.ny);
  }

}
