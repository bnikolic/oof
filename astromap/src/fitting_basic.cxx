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
  
  ModelMap::ModelMap(void):
    worldcs(true)
  {
  }

  ModelMap::~ModelMap()
  {
  }

  ModelMapFn::ModelMapFn(void):
    model(NULL)
  {
  }

  void ModelMapFn::eval(Map &m) const
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

  void ModelMapFn::SetModel(BNLib::BinaryDD * mod)
  {
    model=mod;
  }
  
  FittableMap::FittableMap(const Map &map):
    map(map),
    mtemp(map)
  {

  }

  void FittableMap::residuals(std::vector<double> &res)  const
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

  GaussMapModel_::GaussMapModel_(void)
  {
    SetModel(&gm);
  }

  void GaussMapModel_::eval(Map &m) const
  {
    ModelMapFn::eval(m);
  }

  void GaussMapModel_::AddParams (std::vector<Minim::DParamCtr> &pars)
  {
    
    pars.push_back(Minim::DParamCtr (&gm.amp,      
				     "amp", 
				     true,                       
				     "Amplitude"
				     ));

    pars.push_back(Minim::DParamCtr (&gm.x0,      
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

  GaussMapModel::GaussMapModel(const AstroMap::Map &mm):
    FittableMap(mm)
  {
  }

  GaussConvMap_::GaussConvMap_(const Map &conv):
    conv(conv)
  {
  }
    
  void GaussConvMap_::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    GaussMapModel_::AddParams(pars);
  }

  void GaussConvMap_::eval(Map &m) const
  {
    boost::scoped_ptr<AstroMap::Map> gmodel(AstroMap::Clone(m));

    GaussMapModel_::eval(*gmodel);    
    
    FFTConvolve(*gmodel, 
		conv,
		m);
  }

  GaussConvMap::GaussConvMap(const Map &obsmap,
			     const Map &conv):
    FittableMap(obsmap),
    GaussConvMap_(conv)
  {
  }





}


