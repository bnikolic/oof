/*
  Bojan Nikolic
  $Id: astromap.cxx,v 1.3 2005/06/21 00:44:44 bnikolic Exp $

*/

#include "astromap.hxx"

#include <bndebug.hxx>

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


  Map & Map::operator= (const Map & m) 
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

  Map * Clone (Map &m)
  {
    return new Map( m.nx, m.ny, m.cs->Clone());
  }

}
