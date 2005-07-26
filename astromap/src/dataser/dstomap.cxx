/*
  Bojan Nikolic
  $Id: dstomap.cxx,v 1.4 2005/07/26 22:20:14 bnikolic Exp $
*/

#include "dstomap.hxx"

#include <gaussian.hxx>

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

	for (unsigned j (0) ; j < pxl.px->size() ; ++j ) 
	  {
	    totc += gfn ((*pxl.px)[j],(*pxl.py)[j]);
	  }
	
	if ( totc > 0 )
	  {
	    // Iterate of the pixels in the pixel list
	    for (unsigned j (0) ; j < pxl.px->size() ; j++ ) 
	      {
		int currpx = (*pxl.px)[j];
		int currpy = (*pxl.py)[j];

		double currweight = gfn (currpx,currpy ) * ds[i].ufnu / totc;

		if ( currweight > 0 ) 
		  {
		    double newweight  = (currweight + 
					 weight->get( currpx, currpy)) ; 
		    
		    double newpixvalue = (ds[i].fnu * currweight   + 
					  (m1.get(currpx,currpy)  * 
					   weight->get(currpx,currpy))) 
		      / newweight;
		    
		    m1.get(currpx,currpy ) =newpixvalue;
		    weight->get(currpx,currpy)=newweight;

		  }
		
	      }
	  }
	
      }
  }
}


