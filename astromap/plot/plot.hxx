/*
  Bojan Nikolic
  $Id: plot.hxx,v 1.3 2005/09/12 18:26:50 bnikolic Exp $

  Main routines for plotting maps
*/

#ifndef _ASTROMAP_PLOT_HXX__
#define _ASTROMAP_PLOT_HXX__

#include "../src/astromap.hxx"

#include <vector>

namespace AstroMap {

  /*! Plots the supplied map as a grayscale */
  void Plot ( Map & m );

  void Plot ( Map & m, double minval, double maxval );


  /*! Contours the supplied map at contour levels supplied in contlevels */
  void Contour ( Map &m , std::vector<double> &contlevels );



}


#endif
