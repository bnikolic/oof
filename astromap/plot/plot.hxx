/*
  Bojan Nikolic
  $Id: plot.hxx,v 1.2 2005/09/05 01:30:31 bnikolic Exp $

  Main routines for plotting maps
*/

#ifndef _ASTROMAP_PLOT_HXX__
#define _ASTROMAP_PLOT_HXX__

#include "../src/astromap.hxx"

namespace AstroMap {

  /*! Plots the supplied map as a grayscale */
  void Plot ( Map & m );

  void Plot ( Map & m, double minval, double maxval );



}


#endif
