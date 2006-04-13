/*
  Bojan Nikolic
  $Id: csops.cxx,v 1.5 2006/04/13 16:16:18 bnikolic Exp $

  Coordinate system operations
*/

#include "csops.hxx"

#include <bndebug.hxx>

#include "../astromap.hxx"
#include "coordsys.hxx"
#include "lincordsys.hxx"


namespace AstroMap {

  void MkApCS(Map &m , double halflen)
  {

    // For the time being assumed we have a linear coordinate system;
    LinCS * lcs = dynamic_cast<LinCS *>( m.cs );
    // This will cause an abort if dynamic cast failed
    ENFORCE(lcs);

    lcs->TM[0] = halflen * 2 / m.nx;
    lcs->TM[1] = 0;
    lcs->TM[2] = -1.0 * halflen  ;
    
    lcs->TM[3] = 0;
    lcs->TM[4] = halflen * 2 / m.ny;
    lcs->TM[5] = -1.0 *  halflen  ;


  }

  void MkRectCS(Map &m, double xhalflen, double yhalflen)
  {
    // For the time being assumed we have a linear coordinate system;

    LinCS * lcs = ENFORCE(dynamic_cast<LinCS *>( m.cs ));


    lcs->TM[0] = xhalflen * 2 / m.nx;
    lcs->TM[1] = 0;
    lcs->TM[2] = -1.0 * xhalflen  ;
    
    lcs->TM[3] = 0;
    lcs->TM[4] = yhalflen * 2 / m.ny;
    lcs->TM[5] = -1.0 *  yhalflen  ;

  }

  void ShrinkCS(Map &m , double cf )
  {

    // For the time being assumed we have a linear coordinate system;
    LinCS * lcs = dynamic_cast<LinCS *>( m.cs );
    // This will cause an abort if dynamic cast failed
    ENFORCE(lcs);

    lcs->TM[0] /= cf;
    lcs->TM[2] /= cf;

    lcs->TM[4] /= cf;
    lcs->TM[5] /= cf;
    
  }

}


