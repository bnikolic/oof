/*
  Bojan Nikolic
  $Id: lincordsys.cxx,v 1.1 2005/06/21 00:44:47 bnikolic Exp $

*/

#include "lincordsys.hxx"

namespace AstroMap {

  
  LinCS::LinCS(void) :
    TM(6)
  {
    // Unit transform
    TM[0] =1;
    TM[1] =0;
    TM[2] =0;
    TM[3] =0;
    TM[4] =1;
    TM[5] =0;
  }

  LinCS::~LinCS()
  {

  }

  const void LinCS::pxtoworld(double px , double py , double &wx , double &wy) 
  {
    const unsigned naxis = 2;

    // Pixel coordinate vector
    std::valarray<double> pc(naxis);
    pc[0] = px;
    pc[1] = py;
    
    // World coordinate vector
    std::valarray<double> wc(naxis);    
    
    for(unsigned  i=0 ; i< naxis ; ++i) 
      {
	wc[i]= TM[ i*(naxis+1) +naxis ];
	for (unsigned j=0 ; j < naxis ; ++j) 
	  {
	    wc[i] += pc[j] * TM[ i*(naxis+1) + j ] ;
	  }
      }

    wx = wc[0];
    wy = wc[1];

  }

}


