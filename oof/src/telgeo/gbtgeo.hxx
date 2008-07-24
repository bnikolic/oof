/**
   \file gbtgeo.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>
*/
#ifndef _OOF_TELGEO_GBTGEO_HXX__
#define _OOF_TELGEO_GBTGEO_HXX__

#include "telgeo.hxx"

namespace OOF {

  /**
     \brief Gemetry at GBT Gregorian focus 
  */
  class  GBTGeo :  
    public  TelGeometry 
  {

    /*! Radius of the primary reflector */
    double PrimRadius;

  public:

    /* -------------- Public data  ---------------*/

    /*! Focal length of the primary */
    double PrimF;
    
    /*! Effective focal length at gregorian focus*/
    double GregF ;

    /* Constructors / Desctructors                  */

    /*! Default constructor sets up for the real GBT */
    GBTGeo(void);

    /* -----------  Member functions --------- */

    /*! Set the provided aperture map to the path change introduced by
     *  movement of the secondary by the given amount. 
     *
     * dX, dY, dZ are in the GBT frame; so, dY is the defocus
     * direction.
     **/
    void MkSubMove ( double dX , double dY, double dZ, AstroMap::Map & Path ) const ;

    /* ------------ Inherited functions -------------*/

    virtual void MkDefocus( double dz , AstroMap::Map & Phase) const  ;

    virtual void DishMask (AstroMap::Map &Dish) const ;

    virtual double DishEffRadius(void) const ;
    
  };

  /*! Calculate path change due to movement of the secondary mirror
   *  from optimal position.
   *
   *  x,y is the positions in the aperture plane to calculate the path
   *  change.  
   *  dX, dY , dZ are the movements of the secondary mirror. 
   */
  double SecDeltaPath (double x, double y,
		       double dX, double dY , double dZ,
		       const GBTGeo & geo);

  /*! A revised version of secdeltapath.
   *
   * Subreflector motions are in the GBT reference system.
   */
  double SecDeltaPathV2 (double x, double y,
			 double XGBT, double YGBT , double ZGBT,
			 const GBTGeo & geo);


  /** \brief GBT geometry with a truncated aperture
   */
  class TruncGBT :
    public GBTGeo
  {

    double primRadius;

  public:
    
    // ---------- Construction / Destruction --------------    

    /**
       \param R The aperture radius to use
     */
    TruncGBT(double R);


    // ---------- Inherited from GBTGeo -------------------

    virtual double DishEffRadius(void) const ;    

  };


  
}
#endif
