/*!
  Bojan Nikolic
  $Id: zernmodel.cxx,v 1.5 2005/08/05 17:29:48 bnikolic Exp $
*/

#include "zernmodel.hxx"

#include <astromap.hxx>
#include <csops.hxx>
#include <lcmaps.hxx>
#include <bndebug.hxx>
#include <zernikepoly.hxx>
#include <mapset.hxx>

#include <boost/format.hpp>
#include <iostream>

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

  RZernModel::RZernModel ( unsigned n , AstroMap::Map & msample, TelGeometry * telgeo ) :
    maxzorder(n),
    lcm( ENFORCE( new AstroMap::LCMaps() ))
  {
    // Save the msample coordinate system
    CSSave csorig (msample);


    if ( dynamic_cast<CassegrainGeo *> (telgeo) ) 
      {
	// Normalise the coordinate system
	ZernCSSetup( msample , 
		     dynamic_cast<CassegrainGeo *> (telgeo)->PrimRadius);
      }

    // Rasterise the zernikes
    RastZerns (  n , msample);

  }
    
  RZernModel::RZernModel ( unsigned n , 
			   AstroMap::Map & msample,
			   CassegrainGeo & telgeo):
    maxzorder(n),
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

  void     RZernModel::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {

    using boost::format;
    using boost::io::str;
    
    for(int n=0; n <= (int)maxzorder; ++n)
      for(int l= -n; l<=n ; l += 2)
	{
	  unsigned seqno = BNLib::ZernIFromNL(n,l);
	  pars.push_back(Minim::DParamCtr ( & lcm->coeffs[ seqno ] ,      
					    str(format("z%i") % seqno ) , 
					    seqno ? true : false ,                       
					    str(format("coeff. of Zernike n=%i , l=%i") % n % l )
					    )); 
	}
  }

}


