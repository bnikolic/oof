/*
  Bojan Nikolic
  $Id: mapops.cxx,v 1.3 2005/10/24 22:37:37 bnikolic Exp $


*/

#include "mapops.hxx"

#include <valarray>
#include <cmath>

#include "astromap.hxx"

#include <bnrandom.hxx>

#include <iostream>


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
    double var = ( (m*m).sum()/ m.size()  - pow( (m.sum()/ m.size() ),2) );

    return sqrt(var);
  }

  double MapRMS( Map &m, Map & weight)
  {
    std::valarray<double> goodmap ( m[weight>0.0] );
    std::valarray<double> goodweight ( weight[weight>0.0] );

    double mean = (goodmap * goodweight).sum() / goodweight.sum() ;

    goodmap *= goodmap;

    double var = (goodmap  * goodweight).sum() / goodweight.sum()  - pow(mean,2);

    return sqrt(var);

  }

}



