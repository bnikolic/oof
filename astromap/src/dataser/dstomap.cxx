/*
  Bojan Nikolic
  $Id: dstomap.cxx,v 1.2 2005/07/26 21:18:47 bnikolic Exp $
*/

#include "dstomap.hxx"

#include <gaussian.hxx>
#include <iostream>

#include "dataseries.hxx"
#include "../astromap.hxx"
#include "../pixextract.hxx"
#include "../coordsys/coordsys.hxx"

namespace AstroMap {
  
  void SimpleDrizzle ( DataSeries &ds , Map &m1, 
		       double extent_px, double fwhm_px )
  {
    // Zero the input map
    m1 *= 0.0;

    std::auto_ptr<Map> weight ( Clone(m1) );

    // Will use these to store the pixel coords of each datapoint
    double px, py;

    for ( unsigned i =0 ; i < ds.size() ; ++i )
      {
	// Get the pixel coordinates of the data point.
	m1.cs->worldtopx( ds[i].dX  , ds[i].dY , px, py);

	PixListInt pxl = ExSquare( (int) px, (int) py, (int) extent_px, m1);

	BNLib::GaussianDD gfn( fwhm_px / 2.35, px, py );
	
	double totc(0);

	for (unsigned i (0) ; i < pxl.px->size() ; ++i ) 
	  {
	    totc += gfn ((*pxl.px)[i],(*pxl.py)[i]);
	  }
	
	if ( totc > 0 )
	  {
	    for (unsigned i (0) ; i < pxl.px->size() ; ++i ) 
	      {
		double currweight = gfn ((*pxl.px)[i],(*pxl.py)[i]) * ds[i].ufnu / totc;
		
		double newweight  = currweight + weight->get((*pxl.px)[i],(*pxl.py)[i]);
		double newpixvalue = (ds[i].fnu * currweight   + 
				      (m1.get((*pxl.px)[i],(*pxl.py)[i])  * 
				       weight->get((*pxl.px)[i],(*pxl.py)[i] ))) 
		  / newweight;

		m1.get((*pxl.px)[i],(*pxl.py)[i] ) =newpixvalue;
		weight->get((*pxl.px)[i],(*pxl.py)[i])=newweight;
		
	      }
	  }
	
      }
  }
}


