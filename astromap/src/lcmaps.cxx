/*
  Bojan Nikolic
  $Id: lcmaps.cxx,v 1.2 2005/08/05 17:34:40 bnikolic Exp $
  
*/

#include "lcmaps.hxx"


namespace AstroMap {
  
  void LCMaps::AddMap (Map &m) 
  {
    maps.push_back(m);
    coeffs.push_back(0);
  }
  
  void LCMaps::Calc(Map &res) const 
  {
    CLCMaps( coeffs ,
	     maps,
	     res);
  }

  size_t LCMaps::size(void) const
  {
    return coeffs.size();
  }

  void CLCMaps( std::vector<double> const & coeffs,
		std::vector<Map> const & maps,
		Map & res)
  {
    // Zer the results map
    res *= 0;

    for ( size_t i = 0 ; i < coeffs.size() ; ++i)
      res += coeffs[i] *  maps[i];
  }

}


