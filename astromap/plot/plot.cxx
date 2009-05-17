/**
   \file plot.cxx
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   Initial version 2003
   Revised 2009
*/

#include "plot.hxx"

#include <bndebug.hxx>

#include "../src/coordsys/lincordsys.hxx"

#include <cpgplot.h>

namespace AstroMap {


  void Plot (Map &m)
  {
    Plot(m, 
	 m.min(),    
	 m.max());
  }

  /*
   * Convert the data to format used by pgplot. I.E., convert the main
   * array to be ploted to float precision and extract and convert the
   * transition matrix.
   */
  void PGData(Map &m, 
	      std::valarray<float> &data, 
	      float *trmatrix)
  {

    // Convert main array to floats.
    data.resize( m.size() );
    
    for( unsigned i =0 ; i < m.size() ; ++i )
      data[i] = m[i];


    // Get the transition matrix

    // Assume that a linear system is being used...
    const LinCS * lcs = ENFORCE(dynamic_cast<const LinCS *>(m.cs));
    // This is just a shortcut
    const std::valarray<double> &TM ( lcs->TM);
    
    trmatrix[0]=TM[2];
    trmatrix[1]=TM[0];
    trmatrix[2]=TM[1];
    trmatrix[3]=TM[5];
    trmatrix[4]=TM[3];
    trmatrix[5]=TM[4];
    
  }


  void Plot(Map &m,
	    double minval,
	    double maxval,
	    size_t xmin,
	    size_t xmax,
	    size_t ymin,
	    size_t ymax)
  {


    // Make a float array to pass to pgplot
    std::valarray<float> data( m.size() );

    // Make a float array to hold the transformation matrix
    float trmatrix[6];
    
    // Convert the data
    PGData( m, data , trmatrix);

    
    cpgimag( &data[0], 
	     m.nx, 
	     m.ny, 
	     xmin , 
	     xmax, 
	     ymin, 
	     ymax,
	     minval, maxval,
	     trmatrix);
  }

  void Plot (Map &m, 
	     double minval, 
	     double maxval)
  {
    Plot(m,
	 minval,
	 maxval,
	 1 , 
	 m.nx, 
	 1, 
	 m.ny);
  }

  void Contour (Map &m , 
		std::vector<double> &contlevels)
  {

    std::valarray<float> data( m.size() );
    float trmatrix[6];

    PGData( m, data , trmatrix);

    // Now convert the contour levels
    std::valarray<float> cl( contlevels.size()) ;
    std::copy(contlevels.begin() , contlevels.end() , &cl[0] );

    cpgcont( &data[0], 
	     m.nx, m.ny, 
	     1 , m.nx, 
	     1 , m.ny,
	     &cl[0], 
	     cl.size(), 
	     trmatrix);
    

    
  }



}



