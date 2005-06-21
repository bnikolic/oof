/*
  Bojan Nikolic
  $Id: phelpers.hxx,v 1.1 2005/06/21 14:21:58 bnikolic Exp $

  Some routines to help out with plotting using pgplot
*/

#ifndef _ASTROAP_PHELPERS_HXX__
#define _ASTROAP_PHELPERS_HXX__

#include <vector>

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
    

}

#endif
