/*!
  Bojan Nikolic
  $Id: zernmodel.cxx,v 1.2 2005/08/04 20:17:44 bnikolic Exp $
*/

#include "zernmodel.hxx"

#include <astromap.hxx>
#include <csops.hxx>



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

  void ZernCSSetup(AstroMap::Map &m , double dishradius)
  {
    AstroMap::ShrinkCS(m , dishradius );
  }


}


