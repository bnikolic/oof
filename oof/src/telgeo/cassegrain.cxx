/*!
  Bojan Nikolic
  $Id: cassegrain.cxx,v 1.4 2005/07/26 21:12:33 bnikolic Exp $

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
    // private classes?
    class DMaskFN  :  public BNLib::BinaryDD
    {
      double innerrad;
      double outerrad;
      
    public:
      
      DMaskFN ( double innerrad , double outerrad ):
	innerrad(innerrad),
	outerrad(outerrad)
      {
      }

      double operator() (double x , double y )
      {
	double r2  = sqrt( x*x + y*y ) ;

	if ( r2  < innerrad ||
	     r2  > outerrad )
	  return 0;
	else
	  return 1.0;
      }
    
    } ;
    
    DMaskFN fn ( SecRadius , PrimRadius );
    WorldSet( Dish , fn );    
    
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
