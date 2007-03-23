/*
  Bojan Nikolic

  
  Linear combinations of maps
*/
#ifndef _ASTROMAP_LCMAPS_HXX__
#define _ASTROMAP_LCMAPS_HXX__

#include <vector>
#include "astromap.hxx"

namespace AstroMap {

  /*! A class to represent a linear combination of maps */
  class LCMaps {
    
    // We'll keep a copy of each of the maps here.
    std::vector<Map> maps;

  public:

    // These are the coefficients of each the maps;
    std::vector<double>    coeffs;

    // ------  Constructors / Destructors -----

    /* Default constructors are OK */


    /*! Add a map the lc set */
    void AddMap (Map &m) ;
    
    /*! Calculate the linear combination and store the results in the
      supplied map res. */
    void   Calc(Map &res) const;

    /*! Return the number of maps in the lc */
    size_t size(void) const;

  };

  /*! Actually calculate a linear combination of maps */
  void CLCMaps( std::vector<double> const & coeffs,
		std::vector<Map> const & maps,
		Map & res);


}


#endif
