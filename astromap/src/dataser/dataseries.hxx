/*
  Bojan Nikolic
  $Id: dataseries.hxx,v 1.4 2005/07/26 21:18:47 bnikolic Exp $

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


}
#endif
