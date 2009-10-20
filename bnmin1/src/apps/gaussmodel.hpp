/**
   \file gaussmodel.hpp
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   Most trivial directly representing gaussian likelihood
*/

#ifndef _BNMIN1_TEST_GAUSSMODEL_HPP__
#define _BNMIN1_TEST_GAUSSMODEL_HPP__

#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

#include "../src/minimmodel.hxx"

namespace u = boost::numeric::ublas;

namespace Minim {

class GaussObs:
  public Minim::MLikelihood
{

public:

  /// Parameters of the model
  u::vector<double> p;    

  /// Scale parameter
  double sigma;

  /**
     \param n Number of parameters/dimensions
   */
  GaussObs(size_t n):
    p(n),
    sigma(1.0)
  {
  }
  
  double lLikely(void) const
  {
    return p.size()* 0.5*std::log(2*M_PI*pow(sigma,2))+ u::inner_prod(p,p)/(2*pow(sigma,2));
  }

  void AddParams(std::vector< Minim::DParamCtr > &pars);


};

}

#endif

