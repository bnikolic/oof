/*
  Bojan Nikolic
  $Id: csops.cxx,v 1.2 2005/07/08 22:04:57 bnikolic Exp $

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

}


