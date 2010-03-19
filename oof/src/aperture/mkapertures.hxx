/**
   \file mkapertures.hxx

   Bojan Nikolic  <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   Functions to make apertures...
*/

#ifndef __OOF_MKAPERTURES_HXX__
#define __OOF_MKAPERTURES_HXX__

#include <astromap_fwd.hxx>
#include <stdlib.h>


namespace  OOF {

  // Forwards
  class ApertureMod;
  class TelGeometry;

  /*! Make an aperture map  */
  AstroMap::Map * MkApMap ( TelGeometry * telgeo ,
			    unsigned npix,
			    double oversample);

  /** \brief Make the standard aperture model class 
      
  Uses: Zernike parameterisation of phase, Gaussian parametrisation of
  amplitude. 
  
  \param npix linear number of pixels to use in maps

  \param nzern maximum order of Zernike polynomials to include in the
  phase parametrisation

  \param oversample sampling factor to use (do not make smaller than
  2.0, otherwise will undersample)
  */
  ApertureMod * MkSimpleAp( TelGeometry * telgeo ,
			    double wavel,
			    unsigned npix,
			    unsigned nzern ,
			    double oversample );

  /** \brief Make the aperture model for ALMA 
      
  */
  ApertureMod *mkALMAAp(TelGeometry *telgeo,
			double wavel,
			unsigned npix,
			unsigned nzern,
			double oversample);


  /** \brief Make the aperture model suitable for MUSTANG/GBT
      
      So far only difference from MkSimpleAp is that top-hat
      illumination is used.
            
   */
  ApertureMod * MkMUSTANGAp( TelGeometry * telgeo ,
			     double wavel,
			     unsigned npix,
			     unsigned nzern ,
			     double oversample );

  /** \brief Make an aperture model suitable for MUSTANG/GBT, with
      possiblity of fitting for relative amplitude
      
      \param nobs Number of observations which constitute this set

   */
  ApertureMod * MkMgMltiAmpAp(TelGeometry * telgeo ,
			      double wavel,
			      unsigned npix,
			      unsigned nzern ,
			      double oversample,
			      size_t nobs);

  



}

#endif
