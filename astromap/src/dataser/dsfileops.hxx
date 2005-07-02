/*!
  Bojan Nikolic
  $Id: dsfileops.hxx,v 1.1 2005/07/02 20:38:09 bnikolic Exp $

  input  / output operations on dataseries

*/

#ifndef _ASTROMAP_DSFILEOPS_HXX__
#define _ASTROMAP_DSFILEOPS_HXX__


namespace AstroMap {

  /* Forwards */
  class DataSeries;

  /*!
   * Load a dataseries from FITS file named fname, extension number
   * extno.
   *
   * This extension should be a binary table with following columns:
   * DX : delta azimuth 
   * DY : delta eleveation 
   * FNU : flux density  observed at this position 
   * UFNU : estimated error in the flux density
   *
   *
   */
  DataSeries * LoadFITSDS( const char * fname , unsigned extno);
  



}

#endif
