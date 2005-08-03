/*!
  Bojan Nikolic
  $Id: zernmodel.cxx,v 1.1 2005/08/03 12:01:42 bnikolic Exp $
*/

#include "zernmodel.hxx"

#include <astromap.hxx>



namespace OOF {

  CSSave::CSSave(AstroMap::Map & m ) :
    m(m),
    csorig( m.cs)
  {
  }

  CSSave::~CSSave()
  {
    m.cs=csorig;
  }



}


