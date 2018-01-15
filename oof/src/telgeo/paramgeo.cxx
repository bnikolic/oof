/**
   2018 Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
*/


#include "paramgeo.hxx"
#include "primefoc.hxx"

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include "zernikepoly.hxx"
#include "../aperture/zernmodel.hxx"
#include "minim.hxx"
#include <mapset.hxx>

namespace OOF {

  ParamGeo::ParamGeo(double R,
		     const parset &zpars):
    _R(R),
    _zpars(zpars)
  {
  }

  void ParamGeo::MkDefocus( double dz , AstroMap::Map & Phase) const
  {
  }

  void ParamGeo::DishMask (AstroMap::Map &Dish) const
  {
    class DMaskFN  :  public BNLib::BinaryDD
    {
      double outerrad;
      
    public:
      
      DMaskFN ( double outerrad ):
	outerrad(outerrad)
      {
      }

      double operator() (double x , double y )
      {
	double r2  = sqrt( x*x + y*y ) ;

	if (  r2  > outerrad )
	  return 0;
	else
	  return 1.0;
      }
    
    } ;
    
    DMaskFN fn ( _R );
    WorldSet( Dish , fn );        
  }


  
  size_t ZernToInt(const std::string &zname)
  {
    boost::regex r("z(\\d+)");
    boost::smatch m;
    boost::regex_match(zname, m, r);
    return boost::lexical_cast<size_t>(m[1]);
  }

  size_t maxZOrder(const parset &zpars)
  {
    size_t n=0;
    for(parset::const_iterator i= zpars.begin();
	i != zpars.end();
	++i)
      {
	int nn; int l;
	BNLib::ZernNLFromI(ZernToInt(i->first), nn, l);
	if (nn> n) n=nn;
      }
    return n;
  }

  void RasterizeZern(const parset &zpars,
		     AstroMap::Map &m,
		     double R)
  {
    PrimeFocusGeo t;
    t.PrimRadius=R;

    size_t maxo=maxZOrder(zpars);


    RZernModel zernm(maxo, 
		     m,
		     &t);
    
    Minim::ModelDesc md(zernm);

    for(parset::const_iterator i= zpars.begin();
	i != zpars.end();
	++i)
      {
	*(md[i->first]->p)=i->second;
      }

    zernm.Calc(m);
    
  }

}
