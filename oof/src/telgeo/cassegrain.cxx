/*!
  Bojan Nikolic
  $Id: cassegrain.cxx,v 1.3 2005/06/25 12:08:57 bnikolic Exp $

*/


#include "cassegrain.hxx"

#include <cmath>

#include <bndebug.hxx>
#include <astromap.hxx>
#include <mapset.hxx>

#include "tdzhelper.hxx"

namespace OOF {



  void CassegrainGeo::MkDefocus( double dz , AstroMap::Map & Phase) const  
  {
    DzHelper<CassegrainGeo> dzfn (*this, dz);
    WorldSet( Phase, dzfn );
  }

  void CassegrainGeo::DishMask (AstroMap::Map &Dish) const 
  {
    // not implemented yet
    ENFORCE(0);
  }

  double SecDeltaPath (double x, double y,
		       double dX, double dY , double dZ,
		       const CassegrainGeo & geo)
  {
    
    /*! Think about  dX, dY a little later.... */
    ENFORCE( dX==0 && dY == 0 );

    double delta=0;

    const double r= sqrt (x*x + y*y);

    /* Change of path due to defocus (dZ) */
    const double a = r / 2.0 / geo.PrimF;
    const double b = r / 2.0 / geo.CasF ;

    delta += dZ * ( (1 - a*a)/(1 + a*a) + (1 - b*b)/(1 + b*b) );

    return delta;

  }

  


}
