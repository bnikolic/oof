/**
   \file plot.hxx
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   
   Initial version 2003

   Main routines for plotting maps
*/

#ifndef _ASTROMAP_PLOT_HXX__
#define _ASTROMAP_PLOT_HXX__

#include "../src/astromap.hxx"

#include <vector>

namespace AstroMap {

  /*! Plots the supplied map as a grayscale */
  void Plot(Map &m);

  void Plot(Map &m,
	    double minval,
	    double maxval);

  /** Plot only a subsection of supplied array
      
   */
  void Plot(Map &m,
	    double minval,
	    double maxval,
	    size_t xmin,
	    size_t xmax,
	    size_t ymin,
	    size_t ymax);


  /*! Contours the supplied map at contour levels supplied in contlevels */
  void Contour(Map &m,
	       std::vector<double> &contlevels);

  void Contour(Map &m,
	       std::vector<double> &contlevels,
	       size_t xmin,
	       size_t xmax,
	       size_t ymin,
	       size_t ymax);



}


#endif
