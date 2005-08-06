/*!
  Bojan Nikolic
  $Id: cssave.cxx,v 1.1 2005/08/06 16:18:27 bnikolic Exp $

*/

#include "cssave.hxx"

namespace AstroMap {

  CSSave::CSSave(AstroMap::Map & m ) :
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


