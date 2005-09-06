/*!
  Bojan Nikolic
  $Id: gbtgeo.cxx,v 1.6 2005/09/06 01:34:07 bnikolic Exp $
*/

#include "gbtgeo.hxx"

#include <cmath>

#include <bndebug.hxx>
#include <astromap.hxx>
#include <mapset.hxx>

#include "tdzhelper.hxx"

namespace OOF {

  GBTGeo::GBTGeo(void) :
    PrimRadius ( 50.0 ),
    PrimF      ( 60.0 ),
    GregF      ( 190.0 )
  {

  }
  
  void GBTGeo::MkDefocus( double dz , AstroMap::Map & Phase) const  
  {
    if ( true )
      {
	DzHelper<GBTGeo> dzfn (*this, dz);
	WorldSet( Phase, dzfn );
      }
    else
      {

	DzHelperFull<GBTGeo, &SecDeltaPathV2 >
	  helper ( *this,  0 , dz , 0);
	WorldSet( Phase, helper );
      }
  }

  void GBTGeo::DishMask (AstroMap::Map &Dish) const 
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

  double GBTGeo::DishEffRadius(void) const 
  {
    return PrimRadius;
  }
  
  
  // Note , these directions are not the directons used in GBT
  // engineering!!!
  double SecDeltaPath (double x, double y,
		       double dX, double dY , double dZ,
		       const GBTGeo & geo)
  {

    /*! Think about  dX, dY a little later.... */
    ENFORCE( dX==0 && dY == 0 );

    const double r_dgtr= M_PI / 180.0;

    const double r_fp  = 60.0;
    const double r_fs  = 190.0;

    const double r_ph  = 36.7 * r_dgtr;
	
    // Angle wrt optical axis of primary of the prime ray travelling to
    // secondary focus.
    const   double r_xi = 12.33 * r_dgtr;

    // The defocus movement resolved 
    double dz1 = dZ * cos (r_ph);
    double dy1 = dZ * sin (r_ph);
  
    double dz2 = dZ * cos (r_ph -r_xi);
    double dy2 = dZ * sin (r_ph -r_xi);
	

    double dp1, dp2 ;
	      
    {
      // r_x, r_y are the telescope coordinate system.
      double r_x=x;
      double r_y=54.0 - y;
		
      double r_r= sqrt ( r_x*r_x + r_y*r_y);
		
      double r_th1;

      if ( r_r != 0.0 ) 
	{
	  r_th1 = 2*atan2(r_r, 2*r_fp);

	  dp1 = dz1 * cos (r_th1) +  dy1 * sin (r_th1) * r_y / r_r ;
	  
	}
      else
	{
	  dp1 = dz1;
	}

    }

    {
      double r_y= -1.0 * y;
      double r_x=x;
      double r_r= sqrt ( r_x*r_x + r_y*r_y);
		
      double r_th2;
		
      if (r_r != 0 ) 
	{
	  r_th2 = 2*atan2(r_r, 2*r_fs); 
	  dp2 = dz2* cos (r_th2)  +  dy2 * sin (r_th2) * r_y / r_r ;
	}
      else
	{
	  dp2 = dz2;
	}

      
    }

    double delta = dp1+dp2;
		
    
    return delta;
  }

  void GBTGeo::MkSubMove ( double dX , double dY, double dZ, 
			   AstroMap::Map & Path ) const 
  {
    DzHelperFull<GBTGeo, &SecDeltaPathV2 >
      helper ( *this,  dX, dY , dZ);
    WorldSet( Path, helper );
  }

  double SecDeltaPathV2 (double x, double y,
			 double XGBT, double YGBT , double ZGBT,
			 const GBTGeo & geo)
  {
    // phi is the angle of the GBT defocus directon (+ve YGBT) to the
    // axis of the parent parraboloid.
    double phi = 36.7 * M_PI / 180 ;

    // delta holds the total path
    double delta= 0;

    // Primary frame:
    {
      // resolve the motion of the subreflector into the principal
      // directions of the parent parraboloid (these are the XOOF,
      // YOOF and ZOOF).

      double XOOF = ZGBT;

      double ZOOF = YGBT * cos(phi ) + XGBT * sin(phi );
      double YOOF = -1.0 * YGBT * sin(phi) + XGBT * cos(phi );

      // Now calculate the coordinates of the point in the parent
      // parraboloid coordinate system.
      double r_x=x;


      
      // This reverses the y axis : should need this!
      // double r_y= 54.0 - y;

      // This is the better convention to adopt
      double r_y=y + 54.0;
		
      double r_r= sqrt ( r_x*r_x + r_y*r_y);

      double rn2= r_r / geo.PrimF / 2;
      
      delta += ZOOF * ( 1 - pow(rn2 , 2) ) / ( 1 + pow(rn2 , 2) );

      delta += -1 * YOOF * 2 * rn2 / ( 1 + pow(rn2 ,2 ) )  * r_y/r_r;
      delta += -1 * XOOF * 2 * rn2 / ( 1 + pow(rn2 ,2 ) )  * r_x/r_r;
      
    }

    // now go into the gregorian frame
    {
      
      const double xi = phi - 12.33 * M_PI / 180;

      double XOOF = ZGBT;

      double ZOOF = YGBT * cos(xi ) + XGBT * sin(xi );
      double YOOF = -1.0 * YGBT * sin(xi) + XGBT * cos(xi );

      double r_x=x;
      double r_y=  -1.0 * y;

      double r_r= sqrt ( r_x*r_x + r_y*r_y);

      double rn2= r_r / geo.GregF / 2;
      
      delta +=  ZOOF * ( 1 - pow(rn2 , 2) ) / ( 1 + pow(rn2 , 2) );

      if (r_r != 0.0 )
	{
	  delta +=  YOOF * 2 * rn2 / ( 1 + pow(rn2 ,2 ) )  * r_y/r_r;
	  delta +=  XOOF * 2 * rn2 / ( 1 + pow(rn2 ,2 ) )  * r_x/r_r;
	}
      else
	{
	  // no extra path is introduced on-axis
	}

      
      

    }

    return delta;

  }


}
