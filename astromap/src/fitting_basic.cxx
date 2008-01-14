/**
  \file fitting_basic.cxx
  Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>
  Initial version January 2008.
*/

#include "fitting_basic.hxx"

#if HAVE_MINIMMODEL_HXX

#include "binaryfn.hxx"
#include "mapset.hxx"

namespace AstroMap {
  
  FittableMap::FittableMap(BNLib::BinaryDD & model,
			   const Map       & map):
    model(model),
    map(map),
    mtemp(map)
  {

  }

  void  FittableMap::residuals ( std::vector< double > & res ) 
  {
    WorldSet(mtemp, model);
    for ( size_t j =0 ; j < map.ny ; ++j) 
      for ( size_t i =0 ; i < map.nx ; ++i)
      {
	res[j* map.nx+ i] = map[i,j]-mtemp[i,j];
      }
  }

  unsigned   FittableMap::nres (void) 
  {
    return map.nx * map.ny;
  }

  GaussMapModel::GaussMapModel( const Map       & map) :
    fm( gm, map)
  {
    
  }

}

#endif //HAVE_MINIMMODEL_HXX
