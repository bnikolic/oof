/*!
  Bojan Nikolic
  $Id: zernmodel.cxx,v 1.3 2005/08/05 13:01:26 bnikolic Exp $
*/

#include "zernmodel.hxx"

#include <astromap.hxx>
#include <csops.hxx>
#include <lcmaps.hxx>
#include <bndebug.hxx>
#include <zernikepoly.hxx>
#include <mapset.hxx>

#include "../telgeo/cassegrain.hxx"



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

  RZernModel::RZernModel ( unsigned n , 
			   AstroMap::Map & msample,
			   CassegrainGeo & telgeo):
    lcm( ENFORCE( new AstroMap::LCMaps() ))
  {

    // Save the msample coordinate system
    CSSave csorig (msample);
    
    // Normalise the coordinate system
    ZernCSSetup( msample , telgeo.PrimRadius);

    // Rasterise the zernikes
    RastZerns (  n , msample);

  }

  RZernModel::~RZernModel()
  {
    delete lcm;
  }

  void RZernModel::RastZerns (  unsigned maxorder , AstroMap::Map &msample)
  {
    for (int  n =0 ; n <= (int)maxorder ; ++n )
      {
	for(int l= -n; l<=n ; l += 2)
	  {
	    //unsigned seqno = BNLib::ZernIFromNL(n,l);

	    BNLib::ZernPoly zp ( n, l);
	    AstroMap::WorldSet( msample , zp);
	    
	    lcm->AddMap(msample);

	  }
      }

  }

  void RZernModel::Calc( AstroMap::Map &m)  const 
  {
    lcm->Calc(m);
  }

}


