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

  /**
     \param n Number of parameters/dimensions
   */
  GaussObs(size_t n):
    p(n)
  {
  }
  
  double lLikely(void) const
  {
    return u::inner_prod(p,p);
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

