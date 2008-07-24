/**
   \file primefoc.cxx
    Bojan Nikolic <bojan@bnikolic.co.uk>
*/

#include "primefoc.hxx"

#include <cmath>

#include <binaryfn.hxx>
#include <astromap.hxx>
#include <mapset.hxx>

namespace OOF {

  void PrimeFocusGeo::MkFocMove ( double dx, double dy , double dz, 
				  AstroMap::Map & Phase) const
  {

    class FocHelper :  public BNLib::BinaryDD {
      PrimeFocusGeo const & geo;
      double dx, dy ,dz;

    public :
      FocHelper( PrimeFocusGeo const & geo,     double dx, double dy ,double dz) :
	geo(geo) , dx(dx) , dy(dy) , dz(dz) 
      {}

      double operator() (double x , double y ) 
      {
	return PrimDeltaPath( x, y , dx, dy, dz, geo);
      }
    };

    FocHelper helper ( *this, dx, dy , dz);
    
    WorldSet( Phase, helper );
  }

  void PrimeFocusGeo::MkDefocus( double dz , AstroMap::Map & Phase) const  
  {
    MkFocMove( 0, 0 , dz , Phase);
  }

  void PrimeFocusGeo::DishMask (AstroMap::Map &Dish) const 
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
    
    DMaskFN fn ( PrimRadius );
    WorldSet( Dish , fn );    
  }

  double PrimeFocusGeo::DishEffRadius(void) const 
  {
    return PrimRadius;
  }

  


  double PrimDeltaPath (double x, double y,
			double dX, double dY , double dZ,
			const PrimeFocusGeo & geo)
  {

    
    // This is the radius from centre of aperture.
    const double r= sqrt (x*x + y*y);

    // Project motions of the subreflector into the plane of the ray.
    const double dXproj = dX * x/ r;
    const double dYproj = dY * y/ r;

    // This is the dimensionless radius
    const double r_norm = r / geo.PrimF ;

    return (dXproj + dYproj) *  r_norm / ( 1 + pow(r_norm/2, 2) )  + 
      dZ * ( 1 - pow(r_norm/2, 2) ) / (1 + pow(r_norm/2,2 ) );




  }


}



