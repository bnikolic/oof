/**
   \file mapops.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   Define some useful operations on maps
*/
#ifndef _ASTROMAP_MAPOPS_HXX__
#define _ASTROMAP_MAPOPS_HXX__

#include <complex>

namespace AstroMap {

  // Forwards
  class Map;

  /*!
   *  Assign a normal distribution of defined by sigma to the supplied
   *  map.
   *
   *  This is _not_ the function to use if you need lots and lots of
   *  random maps. The reson for this is that each call uses a new 
   *  random number generator which only seeded from the sysclock --
   *   bound to be less random than a real sequence.  void
   *  
   */
  void NormDist(Map &m, double sigma);

  /*!
   * Calculate the RMS value of the map
   */
  double MapRMS( Map &m);

  /*!
   * This function is misnamed: it actually calculates the standard
   * deviation of the supplied map weighted by the map weight.
   */
  double MapRMS( Map &m, Map & weight);

  /*!
   *  Create a map that is scale times bigger than m, with the pixel
   *  values replicated to fill up the bigger map.
   */
  Map *  IntZoom( Map &m, unsigned scale);

  /** Create a map that is a rectangular subset of the given map
   */
  Map * MapSubset(Map &m, 
                  size_t xlow, size_t xhigh,
                  size_t ylow, size_t yhigh);
  
    

  /** \brief Calculate the complex sum from amplitude and phase maps.
      
  \f[ \sum_j A_j e^{i \phi_j}
  \f]
  \param amp amplitude map (\f$ A\f$)
  \param phase phase map   (\f$ \phi\f$)
   */
  std::complex<double> ComplexSum( const Map & amp,
				   const Map & phase);

  /** \brief Replace not-a-number values or infinities with specified value
   */
  void ReplaceInfNaN ( Map &m,
		       double val);

  /** Assign a Kolmogorov distribution the the supplied map */
  void KolmogorovMap( Map &m );

  /** Assign a broken-power law Kolmogorov distribuition: below
      normalised length w the law is assumed to be thick-screen (5/3)
      above w it is thin-screen (2/3).
  */
  void KolmogorovMap( Map &m,
		      double w);
}


#endif
