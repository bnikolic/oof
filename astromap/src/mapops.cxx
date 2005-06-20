/*
  Bojan Nikolic
  $Id: mapops.cxx,v 1.1 2005/06/21 00:44:44 bnikolic Exp $


*/

#include "mapops.hxx"
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

}



