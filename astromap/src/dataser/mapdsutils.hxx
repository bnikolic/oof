/**
   \file mapdsutils.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>

   September 2007

   Utility free-standing functions for use in map to ds conversions
*/
#ifndef _ASTROMAP_DS_MAPDSUTILS__
#define _ASTROMAP_DS_MAPDSUTILS__

namespace AstroMap {
  
  // Forwards;
  class Map;
  class DataSeries;

  /** \brief Turn a map to a set of positions in a dataseries.

  Note that the "value" elements are not filled in -- use MapDSEval
  for that.

  */
  DataSeries * MapToDSPoss( const Map & m);
			    

}


#endif
