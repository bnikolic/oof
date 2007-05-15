/*
  Bojan Nikolic
  $Id: coordsys.cxx,v 1.1 2005/06/09 13:44:22 bnikolic Exp $

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
