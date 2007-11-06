/**
   \file coordsys.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>

*/

#include "coordsys.hxx"

namespace AstroMap {

  double  CoordSys::x_pxtoworld(double px , double py ) 
  {
    double wx; double wy;
    pxtoworld(px, py , wx , wy);
    return wx;
  }

  double  CoordSys::y_pxtoworld(double px , double py ) 
  {
    double wx; double wy;
    pxtoworld(px, py , wx , wy);
    return wy;
  }

  double  CoordSys::x_worldtopx(double wx, double wy ) 
  {
    double px ; double py;
    worldtopx( wx , wy, px, py );
    return px;
  }

  double  CoordSys::y_worldtopx(double wx, double wy ) 
  {
    double px ; double py;
    worldtopx( wx , wy, px, py );
    return py;
  }



}
