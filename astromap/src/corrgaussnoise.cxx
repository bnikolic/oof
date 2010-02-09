/**
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   Initial version February 2010
   
   This file is part of AstroMap.

   \file corrgaussnoise.cxx

*/


#include <boost/random/uniform_01.hpp>
#include <boost/random/mersenne_twister.hpp>


#include "corrgaussnoise.hxx"
#include "astromap.hxx"


namespace AstroMap {

    void CorrGaussGauss(Map &m, 
			double sigma,
			double r_px)
    {
      Map namp(m), nphi(m);

      boost::mt19937 intgen;
      boost::uniform_01<boost::mt19937> gen(intgen);
      
      
      double xmid=0.5*m.nx;
      double ymid=0.5*m.ny;
      for (size_t x=0;  x<m.nx; ++x)
      {
	for (size_t y= 0; y<m.ny; ++y) 
	{
	  namp.get(x,y)= sigma*std::exp( -0.5 / std::pow(r_px,2) *
					 (std::pow(x-xmid,2) +
					  std::pow(y-ymid,2)));
	  nphi.get(x,y)= 2*M_PI*gen();
	}
	
      }
      
      
    }
   

}


