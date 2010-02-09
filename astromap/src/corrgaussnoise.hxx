/**
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   Initial version February 2010
   
   This file is part of AstroMap.

   \file corrgaussnoise.hxx

   Routines to create maps with correlated Gaussian noise
   
*/

#ifndef _ASTROMAP_CORRGAUSSNOISE_HXX__
#define _ASTROMAP_CORRGAUSSNOISE_HXX__



namespace AstroMap {

  // Forward declarations
  class Map;

  /** Create a correlated Gaussian noise map which has a Gaussian
      power-spectrum with cutoff r_px
      
      \param m The map to store the result in
      \param sigma The desired rms fluctuation
      \param r_px The power spectrum cutoff in pixels
   */
  void CorrGaussGauss(Map &m, 
		      double sigma,
		      double r_px);
   

}

#endif
