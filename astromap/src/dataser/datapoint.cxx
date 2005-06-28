/*
  Bojan Nikolic
  $Id: datapoint.cxx,v 1.1 2005/06/28 13:47:54 bnikolic Exp $

*/

#include "datapoint.hxx"

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


