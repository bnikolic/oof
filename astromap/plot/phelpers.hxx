/*
  Bojan Nikolic
  $Id: phelpers.hxx,v 1.3 2005/07/09 12:59:09 bnikolic Exp $

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

  /*! Parse a colour table file */
  void ParseCTFile(const char *fname , 
		   std::vector<double> &r,
		   std::vector<double> &g,
		   std::vector<double> &b);

  /*! Set a colour table in PGPlot from a file */
  void  SetFileColourTab (const char * name, double locut=0 , double hicut=1.0);
    

}

#endif
