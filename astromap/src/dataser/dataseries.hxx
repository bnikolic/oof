/*
  Bojan Nikolic
  $Id: dataseries.hxx,v 1.5 2005/09/06 00:18:28 bnikolic Exp $

  Data series support
*/

#ifndef _ASTROMAP_DATASERIES_HXX__
#define _ASTROMAP_DATASERIES_HXX__

#include "datapoint.hxx"

#include <valarray>


namespace AstroMap {

  typedef std::valarray<DataPoint> DSBase ;

  class DataSeries : public DSBase  {

  public:

    /* -------- Constructors & Destructors ----- */

    /*!
     * Create a dataseries of length len 
     */
    DataSeries( size_t len);

    DataSeries( void );


  };

  /*! Invert the data series through the origin, i.e., reverse the
   *  signs of both dX and dY */
  void InvertDS ( DataSeries &ds);


}
#endif
