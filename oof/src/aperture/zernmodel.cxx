/**
   \file zernmodel.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>

*/

#include "zernmodel.hxx"

#include <astromap.hxx>
#include <coordsys.hxx>
#include <csops.hxx>
#include <lcmaps.hxx>
#include <bndebug.hxx>
#include <zernikepoly.hxx>
#include <mapset.hxx>
#include <cssave.hxx>

#include <boost/format.hpp>
#include <iostream>
#include <memory>

#include "../oof_err.hxx"
#include "../telgeo/cassegrain.hxx"



namespace OOF {



  void ZernCSSetup(AstroMap::Map &m , double dishradius)
  {
    AstroMap::ShrinkCS(m , dishradius );
  }

  void RZernModel::checkNZern(size_t nz, 
			      const AstroMap::Map &msample)
  {
    if( nz >= msample.nx/2 )
    {
      throw UseError("Maximum Zernike order too high given map size");
    }
  }

  RZernModel::RZernModel(unsigned n, 
			 AstroMap::Map & msample, 
			 TelGeometry * telgeo) :
    maxzorder(n),
    lcm( ENFORCE( new AstroMap::LCMaps() ))
  {
    checkNZern(n, msample);

    // Calculate the dish mask
    std::auto_ptr<AstroMap::Map> mask ( AstroMap::Clone(msample)) ;
    telgeo->DishMask(*mask);

    // Save the msample coordinate system
    AstroMap::CSSave csorig (msample);

    if ( dynamic_cast<CassegrainGeo *> (telgeo) ) 
      {
	// Normalise the coordinate system
	ZernCSSetup( msample , 
		     dynamic_cast<CassegrainGeo *> (telgeo)->PrimRadius);
      }
    else 
      {
	// Normalise the coordinate system
	ZernCSSetup( msample , 
		     telgeo->DishEffRadius() );
      }


    // Rasterise the zernikes
    RastZerns (  n , msample, *mask);

  }
    
  RZernModel::~RZernModel()
  {
    delete lcm;
  }

  void RZernModel::RastZerns (  unsigned maxorder , 
				AstroMap::Map &msample,
				AstroMap::Map & mask )
  {

    for (int  n =0 ; n <= (int)maxorder ; ++n )
      {
	for(int l= -n; l<=n ; l += 2)
	  {
	    
	    // Apply the zernike poly to the map
	    BNLib::ZernPoly zp ( n, l);
	    AstroMap::WorldSet( msample , zp , mask != 0.0 );
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

  void RZernModel::ZeroTilt(void) 
  {
    lcm->coeffs[1] = 0;
    lcm->coeffs[2] = 0;
  }

}


