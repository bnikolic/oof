/**
   \file datapoint.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>

   DataPoint: a value and value error associted  with a 2D position
*/
#ifndef _ASTROMAP_DATAPOINT_HXX___
#define _ASTROMAP_DATAPOINT_HXX___

namespace AstroMap {

  /*! The class used to represent the position of a data point
   *
   */
  struct DataPos {
    
    /*! Position in the x-coordinate */
    double dX ; 

    /*! Position in the y-coordinate */
    double dY ;
  };

  /*! 
   * Associates a measured value and error with a position on the
   * plane.
   */
  struct DataPoint : public DataPos { 
    
    double fnu;
    double ufnu;

  };



}

#endif
