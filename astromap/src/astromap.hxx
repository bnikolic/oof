/*
  \file astromap.hxx

  Bojan Nikolic

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
    
    /* ----------- Public data members --------------------*/

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

    /**
       Can make copies, but only of maps with the same
       dimensions. Otherwise an exception will be raised.
    */
    const Map & operator= (const Map & m);

    /* ----  Element access  ---------------- */
    
    double & get(unsigned x , unsigned y );

    const double & get(unsigned x , unsigned y ) const;

    /** Returns true if the pixel lies within map boundaries */
    bool belongs(unsigned x , unsigned y) const 
    { return x>=0 && x<nx && y >=0 && y< ny ; }

    bool belongs(int x , int y) const 
    { return x>=0 && x< (int)nx && y >=0 && y< (int)ny ; }

    bool belongs(double x , double y) const 
    { return x>=0 && x<nx && y >=0 && y< ny ; }

    // ---------- Misc mathemathics stuff ------------

    /// In-place square root of the elements
    void sqrt(void);    


  };

  /*!
   * Create a new map idential in every way to the supplied map except
   * that contents are not copied. Note: this will need to be updated
   * when more data structures are added to Map.
   */
  Map * Clone (Map &m);
  



}

#endif
