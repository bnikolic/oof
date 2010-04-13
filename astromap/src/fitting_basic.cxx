/**
  \file fitting_basic.cxx
  Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>
  Initial version January 2008.
*/

#include <boost/scoped_ptr.hpp>


#include "fitting_basic.hxx"

#include "binaryfn.hxx"
#include "mapset.hxx"
#include "convolve.hxx"

namespace AstroMap {
  
  FittableMap::FittableMap(  const Map       & map):
    model(NULL),
    map(map),
    mtemp(map),
    worldcs(true)
  {

  }

  void FittableMap::SetModel(BNLib::BinaryDD * mod)
  {
    model=mod;
  }

  void FittableMap::eval(Map &m) const
  {
    if (worldcs) 
    {
      WorldSet(m, *model);
    }
    else
    {
      PixelSet(m, *model);
    }
  }

  void FittableMap::residuals( std::vector< double > & res )  const
  {
    eval(mtemp);

    for ( size_t j =0 ; j < map.ny ; ++j) 
      for ( size_t i =0 ; i < map.nx ; ++i)
      {
	res[j* map.nx+ i] = map.get(i,j)-mtemp.get(i,j);
      }
  }

  unsigned FittableMap::nres(void) const
  {
    return map.nx * map.ny;
  }

  Map * FittableMap::ScratchCopy(void)
  {
    return new Map(mtemp);
  }

  GaussMapModel::GaussMapModel( const AstroMap::Map & mm) :
    FittableMap( mm )
  {
    SetModel( & gm);
  }

  void GaussMapModel::eval(Map &m) const
  {
    FittableMap::eval(m);
  }

  void  GaussMapModel::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    
    pars.push_back(Minim::DParamCtr ( & gm.amp ,      
				      "amp", 
				      true     ,                       
				      "Amplitude "
				      ));

    pars.push_back(Minim::DParamCtr ( & gm.x0 ,      
				      "x0", 
				      true     ,                       
				      "x position "
				      ));

    pars.push_back(Minim::DParamCtr ( & gm.y0 ,      
				      "y0", 
				      true     ,                       
				      "y position "
				      ));

    pars.push_back(Minim::DParamCtr ( & gm.sigma ,      
				      "sigma", 
				      true     ,                       
				      "sigma "
				      ));

    pars.push_back(Minim::DParamCtr ( & gm.diff ,      
				      "diff", 
				      true     ,                       
				      "fiff "
				      ));

    pars.push_back(Minim::DParamCtr ( & gm.rho ,      
				      "rho", 
				      true     ,                       
				      "rho "
				      ));
  }

  GaussConvMap::GaussConvMap(const Map &obsmap,
			     const Map &conv):
    GaussMapModel(obsmap),
    conv(conv)
  {
  }
    

  void GaussConvMap::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    GaussMapModel::AddParams(pars);
  }

  void GaussConvMap::eval(Map &m) const
  {
    boost::scoped_ptr<AstroMap::Map> gmodel(AstroMap::Clone(m));

    GaussMapModel::eval(*gmodel);    
    
    FFTConvolve(*gmodel, 
		conv,
		m);
  }

}


