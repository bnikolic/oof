/*
  Bojan Nikolic
  $Id: phelpers.hxx,v 1.2 2005/07/09 10:21:29 bnikolic Exp $

  Some routines to help out with plotting using pgplot
*/

#ifndef _ASTROAP_PHELPERS_HXX__
#define _ASTROAP_PHELPERS_HXX__

#include <vector>
#include <string>

namespace AstroMap {

  /*!
   *Set the PGPlot colour table.
   */
  void SetColourTable (std::vector<double> &l ,
		       std::vector<double> &r, 
		       std::vector<double> &g ,
		       std::vector<double> &b, 
		       double contrast, double brightnes );

  /*! 
   * Make a simple colour table suitable for printing to paper
   */
  void SetPrintCT (double locut , double hicut);

  /*! Return the full path-name of a specified colour map. Compares
   * the supplied name to a list of known cmaps; if not know assumes
   * that name is the filename of the map.
   */
  std::string ColourTFName( const char * name);
    
    

}

#endif
