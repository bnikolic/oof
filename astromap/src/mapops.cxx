/*
  Bojan Nikolic
  $Id: mapops.cxx,v 1.2 2005/10/24 22:04:47 bnikolic Exp $


*/

#include "mapops.hxx"

#include <valarray>
#include <cmath>

#include "astromap.hxx"

#include <bnrandom.hxx>


namespace AstroMap {

  void NormDist(Map &m, double sigma)
  {
    using namespace BNLib;

    NormDistZM nd(sigma);
    nd.reseed(TimeSeed());

    for (unsigned i =0 ; i < m.size() ; ++i)
      m[i]= nd.sample();

  }

  double MapRMS( Map &m)
  {
    double var = ( (m*m).sum() - pow((m.sum()),1) );
    return sqrt(var);
  }

  double MapRMS( Map &m, Map & weight)
  {
    std::valarray<double> wmap ( m * weight / weight.sum() );
    double var = ( (wmap*wmap).sum() - pow((wmap.sum()),1) );
    return sqrt(var);

  }

}



