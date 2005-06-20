/*
  Bojan Nikolic
  $Id: astromap.hxx,v 1.3 2005/06/21 00:44:44 bnikolic Exp $

*/
#ifndef _ASTROMAP_ASTROMAP_HXX__
#define _ASTROMAP_ASTROMAP_HXX__

#include <valarray>


namespace AstroMap {

  /* Forwards */
  class CoordSys;

  typedef std::valarray<double> MapBase;

  /*!
   *  2-d map 
   */
  class Map : public MapBase {
    

  public:
    


    /*! Extent in the x direction (first index) */
    const unsigned nx;
    /*! Extent in the y direction */
    const unsigned ny;

    /*! Pointer to the coordiante system class. Will own and destroy
     *  this pointer at end of life.  
     *
     *  Can this be made a const pointer?
     */
    CoordSys * cs;

    
    /* ----- Constructors & destructors ---- */
    
    Map(unsigned nx , unsigned ny );

    Map(unsigned nx , unsigned ny, CoordSys *cs );

    Map(const Map& m);

    ~Map();
    
    /* ------ Operators    -------*/
    Map & operator= (const Map & m);

    /* ----  Element access  ---------------- */
    
    double & get(unsigned x , unsigned y );

    const double & get(unsigned x , unsigned y ) const;
    

  };

  /*!
   * Create a new map idential in every way to the supplied map except
   * that contents are not copied. Note: this will need to be updated
   * when more data structures are added to Map.
   */
  Map * Clone (Map &m);
  



}

#endif
