/*!
  Bojan Nikolic
  $Id: cssave.cxx,v 1.2 2005/08/06 16:19:54 bnikolic Exp $

*/

#include "cssave.hxx"

#include "../astromap.hxx"
#include "coordsys.hxx"

namespace AstroMap {

  CSSave::CSSave(Map & m ) :
    m(m),
    csorig( m.cs )
  {
    m.cs=(*m.cs).Clone();
  }

  CSSave::~CSSave()
  {
    delete m.cs;
    m.cs=csorig;
  }
  


}


