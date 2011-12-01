/**
   \file lcmaps.cxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>
  
*/

#include "lcmaps.hxx"


namespace AstroMap {

  LCMaps *LCMaps::clone(void)
  {
    return new LCMaps(*this);
  }
  
  void LCMaps::AddMap (const Map &m) 
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
    // Zero the results map
    res *= 0;
    size_t msize=res.size();
    for ( size_t i = 0 ; i < coeffs.size() ; ++i)
    {
      const double cc=coeffs[i];
      const Map &cm=maps[i];
      for(size_t j=0; j<msize; ++j)
        res[j] += cc *  cm[j];
    }
  }

}


