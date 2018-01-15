/**
   2018 Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
*/


#include "paramgeo.hxx"
#include "primefoc.hxx"

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include "zernikepoly.hxx"

namespace OOF {

  ParamGeo::ParamGeo(double R,
		     const std::vector< Minim::DParamCtr > &zpars):
    _R(R)
  {
  }

  size_t ZernToInt(const std::string &zname)
  {
    boost::regex r("z(\\d+)");
    boost::smatch m;
    boost::regex_match(zname, m, r);
    return boost::lexical_cast<size_t>(m[0]);
  }

  size_t maxZOrder(const std::vector< Minim::DParamCtr > &zpars)
  {
    size_t n=0;
    for(std::vector< Minim::DParamCtr >::const_iterator i= zpars.begin();
	i != zpars.end();
	++i)
      {
	size_t nn; size_t l;
	BNLib::ZernNLFromI(ZernToInt(i->name), nn, l);
	if (nn> n) n=nn;
      }
    return n;
  }

  void RasterizeZern(const std::vector< Minim::DParamCtr > &zpars,
		     AstroMap::Map &m,
		     double R)
  {
    PrimeFocusGeo t;
    t.PrimRadius=R;


//    RZernModel zernm(unsigned n, 
//		     AstroMap::Map & msample,
//		     TelGeometry * telgeo);
  }

}
