/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2010

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file spheres.hxx

   Computation and use of spheres releated to sets of points
*/
#ifndef  _BNMIN1_SETS_SPHERES_HXX__
#define  _BNMIN1_SETS_SPHERES_HXX__

#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace Minim {

  namespace ublas=boost::numeric::ublas;  

  template<class T>
  void UnifromSphereSurface(T &rng,
			    ublas::vector<double> &v)
  {
    boost::variate_generator<T, 
      boost::normal_distribution<> > 
      normgen(rng, 
	      boost::normal_distribution<>());
    for (size_t i=0; i<v.size(); ++i)
      v[i]=normgen();
    v= v/ublas::norm_2(v);
    
  }

}
#endif
