/**
   \file gaussmodel.hpp
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   Most trivial directly representing gaussian likelihood
*/

#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

#include "../src/minimmodel.hxx"

namespace u = boost::numeric::ublas;


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
    return 0.5*std::log(2*M_PI*pow(sigma,2))+ u::inner_prod(p,p)/(2*pow(sigma,2));
  }

  void AddParams(std::vector< Minim::DParamCtr > &pars)
  {
    using namespace Minim;
    for (size_t i=0; i<p.size(); ++i)
    {
      ParamCtr<double> pa( &p[i], 
			   (boost::format("p%i") % i).str(), 
			   true, 
			   "n-th parameter");
      pars.push_back(pa);
    }

  }
  
};

