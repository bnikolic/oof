/*
  Bojan Nikolic
  $Id: plot.cxx,v 1.1 2005/06/21 14:21:58 bnikolic Exp $

*/

#include "plot.hxx"

#include <bndebug.hxx>

#include "../src/coordsys/lincordsys.hxx"

#include <cpgplot.h>

namespace AstroMap {

  void Plot ( Map & m )
  {

    // Make a float array to pass to pgplot
    std::valarray<float> data( m.size() );
    // And copy the data
    for( unsigned i =0 ; i < m.size() ; ++i )
      data[i] = m[i];

    // Make a float array to hold the transformation matrix
    float trmatrix[6];

    // Assume that a linear system is being used...
    const LinCS * lcs = ENFORCE(dynamic_cast<const LinCS *>(m.cs));
    // This is just a shortcut
    const std::valarray<double> &TM ( lcs->TM);
    
    // For the time being fill up with unit transform
    trmatrix[0]=TM[2];
    trmatrix[1]=TM[0];
    trmatrix[2]=TM[1];
    trmatrix[3]=TM[5];
    trmatrix[4]=TM[3];
    trmatrix[5]=TM[4];

    
    cpgimag( &data[0], 
	     m.nx, 
	     m.ny, 
	     1 , 
	     m.nx, 
	     1, 
	     m.ny,
	     m.min(), 
	     m.max(), 
	     trmatrix);
    

  }



}



