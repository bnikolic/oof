/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2010

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

*/

#include "ellipsoids_sample.hxx"
#include "spheres.hxx"
#include "cholesky.hpp"

namespace Minim {

  EllipsoidSampler::EllipsoidSampler(ublas::matrix<double> Q,
				     ublas::vector<double> c,
				     boost::mt19937 &rng):
    rng(rng),
    Qu(Q.size1(), Q.size2()),
    c(c)
  {
    cholesky_decompose(Q, Qu);
  }

  void EllipsoidSampler::operator()(ublas::vector<double> &v)
  {
    v.resize(c.size());
    ublas::vector<double> s(v.size());
    UnifromSphereVolume(rng, s);    

    v=ublas::solve(Qu, s, ublas::lower_tag());
    
  }


}


