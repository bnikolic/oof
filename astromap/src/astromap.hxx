/*
  Bojan Nikolic
  $Id: astromap.hxx,v 1.2 2005/06/06 13:37:05 bnikolic Exp $

*/
#ifndef _ASTROMAP_ASTROMAP_HXX__
#define _ASTROMAP_ASTROMAP_HXX__

#include <valarray>


namespace AstroMap {

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

    
    /* ----- Constructors & destructors ---- */
    
    Map(unsigned nx , unsigned ny );

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
