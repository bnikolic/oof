/*
  Bojan Nikolic
  $Id: dstomap.cxx,v 1.3 2005/07/26 22:15:37 bnikolic Exp $
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

	for (unsigned j (0) ; j < pxl.px->size() ; ++j ) 
	  {
	    totc += gfn ((*pxl.px)[j],(*pxl.py)[j]);
	  }
	//std::cerr<<px<<" "<<py<<" "<<totc << std::endl;
	
	if ( totc > 0 )
	  {
	    for (unsigned j (0) ; j < pxl.px->size() ; j++ ) 
	      {
		double currweight = gfn ((*pxl.px)[j],(*pxl.py)[j]) * ds[i].ufnu / totc;

		//std::cerr<<px<<" "<<py<<" "<<totc << std::endl;
		//std::cerr<<(*pxl.px)[i]<<" "<<(*pxl.py)[i]<<" "<<currweight<<" " << ds[i].fnu<<std::endl << std::endl;

		if ( currweight > 0 ) 
		  {
		    double newweight  = currweight + weight->get((*pxl.px)[j],(*pxl.py)[j]);
		    
		    double newpixvalue = (ds[i].fnu * currweight   + 
					  (m1.get((*pxl.px)[j],(*pxl.py)[j])  * 
					   weight->get((*pxl.px)[j],(*pxl.py)[j] ))) 
		      / newweight;
		    
		    m1.get((*pxl.px)[j],(*pxl.py)[j] ) =newpixvalue;
		    weight->get((*pxl.px)[j],(*pxl.py)[j])=newweight;

		    //std::cerr<<ds[i].fnu<<" "<<newweight<<" " <<newpixvalue<<" "<<currweight<<std::endl;
		  }
		
	      }
	  }
	
      }
  }
}


